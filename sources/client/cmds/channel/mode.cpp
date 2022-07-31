#include "channel.hpp"

void	irc::cmd::mode(Command* cmd)
{
	if (cmd->getArgC() < 1)
		return (cmd->setResult(ERR_NEEDMOREPARAMS));
	// std::cout << cmd->getArgs()[0] << "," << cmd->getArgs()[1] << std::endl;
	const std::string&	targ = cmd->getArgs()[0];

	// const std::string&	mstr = cmd->getArgs()[1];

	if (targ[0] == '#' || targ[0] == '&') //channel mode
	{
		if (!cmd->getServer()->hasChannel(targ.c_str() + 1))
			return (cmd->setResult(ERR_NOSUCHCHANNEL));
		Channel*	channel = cmd->getServer()->getChannel(targ.c_str() + 1);
		if (!channel->isMember(cmd->getClient()))
			return (cmd->setResult(ERR_NOTONCHANNEL));

		if (cmd->getArgC() > 1)
		{
			const std::string&	mstr = cmd->getArgs()[1];
			std::string::const_iterator	it = mstr.begin();
			char	ad = 0;
			while (it != mstr.end())
			{
				if (*it == '-')
					ad = 1;
				else if (*it == '+')
					ad = 2;
				else if (ad && (*it == 'o' || *it == 'p' || *it == 's' || *it == 'i'
							|| *it == 't' || *it == 'n' || *it == 'b' || *it == 'v'))
				{
					if (ad == 1)
						channel->unsetMode(*it);
					else
						channel->setMode(*it);
				}
				else
					return (cmd->setResult(ERR_UNKNOWNCOMMAND));
				++it;
			}
		}

		return (cmd->setResult(RPL_CHANNELMODEIS, "#" + channel->getName() + " +" + channel->getModestr()));
	}
	else // user mode
	{
		Client*	client = cmd->getServer()->getClient(targ);
		if (!client)
			return (cmd->setResult(ERR_NOSUCHNICK));

		if (cmd->getArgC() > 1)
		{
			const std::string&	mstr = cmd->getArgs()[1];
			std::string::const_iterator	it = mstr.begin();
			char	ad = 0;
			while (it != mstr.end())
			{
				if (*it == '-')
					ad = 1;
				else if (*it == '+')
					ad = 2;
				else if (ad && (*it == 'i' || *it == 's' || *it == 'w' || *it == 'o'))
				{
					if (ad == 1)
						client->unsetMode(*it);
					else
						client->setMode(*it);
				}
				else
					return (cmd->setResult(ERR_UNKNOWNCOMMAND));
				++it;
			}
		}

		std::cout << client->getNick() << " modes:[" << client->getModestr() << "]" << std::endl;
		return (cmd->setResult(RPL_UMODEIS));
	}
}