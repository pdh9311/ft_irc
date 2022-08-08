#include "channel.hpp"

static bool	_is_server_modes(const char c)
{
	return (c == 'p' || c == 's' || c == 'i' ||
			c == 't' || c == 'n' || c == 'm');
}

static bool	_is_user_modes(const char c)
{
	return (c == 'o' || c == 'O' || c == 'a' || c == 'i' ||
			c == 'w' || c == 'r' || c == 's' || c == 'v');
}

static char	_check_sms(std::string str)
{
	std::string::const_iterator	it = str.begin();
	while (it != str.end())
	{
		if (*it != '+' && *it != '-' && !_is_server_modes(*it))
			return (*it);
		++it;
	}
	return (0);
}

static char	_check_ums(std::string str)
{
	std::string::const_iterator	it = str.begin();
	while (it != str.end())
	{
		if (*it != '+' && *it != '-' && !_is_user_modes(*it))
			return (*it);
		++it;
	}
	return (0);
}

static void	_server_mode(irc::Command* cmd)
{
	const std::string&	name = cmd->getArgs()[0];
	irc::Server*		serv = cmd->getServer();
	irc::Client*		cli = cmd->getClient();
	irc::Channel*		chan = serv->getChannel(name);

	if (!chan)
		return (cmd->queue(ERR_NOSUCHCHANNEL, name + " :No such channel"));
	if (!chan->isMember(cli))
		return (cmd->queue(ERR_NOTONCHANNEL, chan->getFName() + " :You're not on that channel"));
	if (cmd->getArgC() < 2)
		return (cmd->queue(RPL_CHANNELMODEIS, chan->getFName() + " +" + chan->getModestr()));
	if (!(chan->hasUserMode(cli, 'o') || chan->hasUserMode(cli, 'O') || cli->hasMode('o')))
		return (cmd->queue(ERR_CHANOPRIVSNEEDED, chan->getFName() + " :You're not channel operator"));
	
	const std::string&	modes = cmd->getArgs()[1];
	std::string::const_iterator	it = modes.begin();
	char	pm = -1;
	std::string	astr;

	if (cmd->getArgC() > 2)
	{
		const std::string&	target = cmd->getArgs()[2];
		irc::Client*		tcli = serv->getClient(target);
		if (!tcli)
			return (cmd->queue(ERR_NOSUCHNICK, target + " :No such nick/channel"));
		if (!chan->isMember(tcli))
			return (cmd->queue(ERR_USERNOTINCHANNEL, tcli->getNick() + " " + chan->getFName() + " :They aren't on that channel"));
		char	invalid = _check_ums(modes);
		if (invalid)
			return (cmd->queue(ERR_UNKNOWNMODE, std::string(":") + invalid + " is unknown mode char to me"));
		while (it != modes.end())
		{
			const char&	c = *it;
			if (c == '-' || c == '+')
			{
				pm = (*it == '-');
				++it;
				continue ;
			}
			else if (pm == -1)
				break ;
			
			size_t	ppos = astr.find_last_of('+');
			size_t	mpos = astr.find_last_of('-');

			if (pm == 0 && !chan->hasUserMode(tcli, c))
			{
				if (ppos == std::string::npos || (mpos != std::string::npos && ppos < mpos))
					astr += '+';
				astr += c;
				chan->setUserMode(tcli, c);
			}
			else if (pm == 1 && chan->hasUserMode(tcli, c))
			{
				if (mpos == std::string::npos || (ppos != std::string::npos && mpos < ppos))
					astr += '-';
				astr += c;
				chan->unsetUserMode(tcli, c);
			}
		
			++it;
		}
		chan->broadcast(cli, "MODE " + chan->getFName() + " " + (astr == "" ? modes : astr) + " " + tcli->getNick());
		return ;
	}

	char	invalid = _check_sms(modes);
	if (invalid)
		return (cmd->queue(ERR_UNKNOWNMODE, std::string(":") + invalid + " is unknown mode char to me"));
	while (it != modes.end())
	{
		const char&	c = *it;
		if (c == '-' || c == '+')
		{
			pm = (*it == '-');
			++it;
			continue ;
		}
		else if (pm == -1)
			break ; // tmp

		size_t	ppos = astr.find_last_of('+');
		size_t	mpos = astr.find_last_of('-');

		if (pm == 0 && !chan->hasMode(c)) // +
		{
			if (ppos == std::string::npos || (mpos != std::string::npos && ppos < mpos))
				astr += '+';
			astr += *it;
			chan->setMode(c);
		}
		else if (pm == 1 && chan->hasMode(c))
		{
			if (mpos == std::string::npos || (ppos != std::string::npos && mpos < ppos))
				astr += '-';
			astr += *it;
			chan->unsetMode(c);
		}
		// else if (!_is_server_modes(*it))
			// return (cmd->queue(ERR_UNKNOWNMODE, std::string(":") + c + " is unknown mode char to me"));
		++it;
	}
	// std::cout << astr << std::endl;
	// cmd->queue(RPL_CHANNELMODEIS, chan->getFName() + " +" + chan->getModestr());
	chan->broadcast(cli, "MODE " + chan->getFName() + " " + astr);
}


static void	_user_mode(irc::Command* cmd)
{
	const std::string&	name = cmd->getArgs()[0];
	// irc::Server*		serv = cmd->getServer();
	irc::Client*		cli = cmd->getClient();
	
	if (cli->getNick() != name)
		return (cmd->queue(ERR_USERSDONTMATCH));
	if (cmd->getArgC() < 2)
		return (cmd->queue(RPL_UMODEIS, "+" + cli->getModestr()));

	const std::string&	modes = cmd->getArgs()[1];
	char	invalid = _check_ums(modes);
	if (invalid)
		return (cmd->queue(ERR_UMODEUNKNOWNFLAG, ":Unknown MODE flag"));
	std::string::const_iterator it = modes.begin();
	char pm = -1;
	while (it != modes.end())
	{
		if (*it == '-' || *it == '+')
		{
			pm = (*it == '-');
			++it;
			continue ;
		}
		else if (pm == -1)
			break ;
		
		if (pm == 0 && !cli->hasMode(*it))
		{
			if (*it != 'o' && *it != 'O' && *it != 'a' && *it != 'v')
				cli->setMode(*it);
		}
		else if (pm == 1 && cli->hasMode(*it))
		{
			if (*it != 'a' && *it != 'r')
				cli->unsetMode(*it);
		}
	
		// else if (!_is_user_modes(*it))
			// return (cmd->queue(ERR_UMODEUNKNOWNFLAG, ":Unknown MODE flag"));
		++it;
	}
	cmd->queue(RPL_UMODEIS, "+" + cli->getModestr());
}

void	irc::cmd::mode(Command* cmd)
{
	if (cmd->getArgC() < 1)
		return (cmd->setResult(ERR_NEEDMOREPARAMS));
	const std::string&	targ = cmd->getArgs()[0];

	if (isChPrefix(targ[0]))
		_server_mode(cmd);
	else
		_user_mode(cmd);
}
