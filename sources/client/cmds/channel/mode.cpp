#include "channel.hpp"

bool	_is_server_modes(const char c)
{
	return (c == 'o' || c == 'p' || c == 's' || c == 'i' ||
			c == 't' || c == 'n' || c == 'b' || c == 'v');
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
	while (it != modes.end())
	{
		const char&	c = *it;
		if (c == '+' || c == '-' || _is_server_modes(*it))
		{
			if (c == '-' || c == '+')
			{
				pm = (*it == '-');
				++it;
				continue ;
			}
			else if (pm == -1)
				break ; // tmp
			if (pm == 0 && !chan->hasMode(c)) // +
				chan->setMode(c);
			else if (pm == 1 && chan->hasMode(c))
				chan->unsetMode(c);
		}
		++it;
	}
	// std::cout << astr << std::endl;
	cmd->queue(RPL_CHANNELMODEIS, chan->getFName() + " +" + chan->getModestr());
}

bool	_is_user_modes(const char c)
{
	return (c == 'o' || c == 'O' || c == 'a' || c == 'i' ||
			c == 'w' || c == 'r' || c == 's');
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
	std::string::const_iterator it = modes.begin();
	char pm = -1;
	while (it != modes.end())
	{
		if (*it == '+' || *it == '-' || _is_user_modes(*it))
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
				if (*it != 'o' && *it != 'O' && *it != 'a')
					cli->setMode(*it);
			}
			else if (pm == 1 && cli->hasMode(*it))
			{
				if (*it != 'a' && *it != 'r')
					cli->unsetMode(*it);
			}
		}
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
