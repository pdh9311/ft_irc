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

	const std::string&	modes = cmd->getArgs()[1];
	std::string::const_iterator	it = modes.begin();
	char	pm = -1;
	std::string	astr;
	while (it != modes.end())
	{
		std::cout << "wat " << *it << std::endl;
		if (*it == '+' || *it == '-' || _is_server_modes(*it))
		{
			if (*it == '-' || *it == '+')
			{
				pm = (*it == '-');
				++it;
				continue ;
			}
			else if (pm == -1)
				break ; // tmp
			
			size_t	ppos = astr.find_last_of('+');
			size_t	mpos = astr.find_last_of('-');
			if (pm == 0 && !chan->hasMode(*it)) // +
			{
				if (ppos == std::string::npos || (mpos != std::string::npos && ppos < mpos))
					astr += '+';
				astr += *it;
				chan->setMode(*it);
			}
			else if (pm == 1 && chan->hasMode(*it))
			{
				if (mpos == std::string::npos || (ppos != std::string::npos && mpos < ppos))
					astr += '-';
				astr += *it;
				chan->unsetMode(*it);
			}
		}
		++it;
	}
	std::cout << astr << std::endl;
	cmd->queue(RPL_CHANNELMODEIS, chan->getFName() + " +" + chan->getModestr());
}

bool	_is_user_modes(const char c)
{
	
}

static void	_user_mode(irc::Command* cmd)
{

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

	// const std::string&	mstr = cmd->getArgs()[1];

	// if (targ[0] == '#' || targ[0] == '&') //channel mode
	// {
	// 	if (!cmd->getServer()->hasChannel(targ.c_str() + 1))
	// 		return (cmd->setResult(ERR_NOSUCHCHANNEL));
	// 	Channel*	channel = cmd->getServer()->getChannel(targ.c_str() + 1);
	// 	if (!channel->isMember(cmd->getClient()))
	// 		return (cmd->setResult(ERR_NOTONCHANNEL));

	// 	if (cmd->getArgC() > 1)
	// 	{
	// 		const std::string&	mstr = cmd->getArgs()[1];
	// 		std::string::const_iterator	it = mstr.begin();
	// 		char	ad = 0;
	// 		while (it != mstr.end())
	// 		{
	// 			if (*it == '-')
	// 				ad = 1;
	// 			else if (*it == '+')
	// 				ad = 2;
	// 			else if (ad && (*it == 'o' || *it == 'p' || *it == 's' || *it == 'i'
	// 						|| *it == 't' || *it == 'n' || *it == 'b' || *it == 'v'))
	// 			{
	// 				if (ad == 1)
	// 					channel->unsetMode(*it);
	// 				else
	// 					channel->setMode(*it);
	// 			}
	// 			else
	// 				return (cmd->setResult(ERR_UNKNOWNCOMMAND));
	// 			++it;
	// 		}
	// 	}

	// 	return (cmd->setResult(RPL_CHANNELMODEIS, "#" + channel->getName() + " +" + channel->getModestr()));
	// }
	// else // user mode
	// {
	// 	Client*	client = cmd->getServer()->getClient(targ);
	// 	if (!client)
	// 		return (cmd->setResult(ERR_NOSUCHNICK));

	// 	if (cmd->getArgC() > 1)
	// 	{
	// 		const std::string&	mstr = cmd->getArgs()[1];
	// 		std::string::const_iterator	it = mstr.begin();
	// 		char	ad = 0;
	// 		while (it != mstr.end())
	// 		{
	// 			if (*it == '-')
	// 				ad = 1;
	// 			else if (*it == '+')
	// 				ad = 2;
	// 			else if (ad && (*it == 'i' || *it == 's' || *it == 'w' || *it == 'o'))
	// 			{
	// 				if (ad == 1)
	// 					client->unsetMode(*it);
	// 				else
	// 					client->setMode(*it);
	// 			}
	// 			else
	// 				return (cmd->setResult(ERR_UNKNOWNCOMMAND));
	// 			++it;
	// 		}
	// 	}

	// 	std::cout << client->getNick() << " modes:[" << client->getModestr() << "]" << std::endl;
	// 	return (cmd->setResult(RPL_UMODEIS));
	// }
}
