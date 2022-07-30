#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "channel/Channel.hpp"
#include "util.hpp"

namespace irc
{
	namespace cmd
	{
		/*
			ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
			ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
			ERR_CHANNELISFULL               ERR_BADCHANMASK
			ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
			RPL_TOPIC
		*/

		// void	join	(Command* cmd)
		// {
		// 	if (!cmd->getArgC())
		// 		return (cmd->setResult(ERR_NEEDMOREPARAMS));

		// 	const std::vector<std::string>	channs = irc::split(cmd->getArgs()[0]);
		// 	Client*	cli = cmd->getClient();
		// 	Server*	serv = cmd->getServer();

		// 	for (size_t i = 0; i < channs.size(); ++i)
		// 	{
		// 		const std::string&	name = channs[i];
				
		// 		if (name[0] == '#')
		// 		{
		// 			Channel*	chan = serv->getChannel(name);
		// 			if (!chan)
		// 				chan = serv->addChannel(name);
		// 			chan->addClient(cli);
		// 			cli->setCChannel(chan);
		// 		}
		// 	}

		// 	const Channel*	chan = cli->getCChannel();
		// 	if (chan && !chan->getTopic().empty())
		// 		cmd->queue(RPL_TOPIC, chan->getFName() + " :" + chan->getTopic());
		// }

		// void	part	(Command* cmd)
		// {
		// 	if (!cmd->getArgC())
		// 		return (cmd->queue(ERR_NEEDMOREPARAMS));

		// 	const std::vector<std::string>	chans = irc::split(cmd->getArgs()[0]);
		// 	Server*	serv = cmd->getServer();
		// 	Client*	cli = cmd->getClient();

		// 	for (size_t i = 0; i < chans.size(); ++i)
		// 	{
		// 		const std::string&	name = chans[i];
		// 		if (name[0] == '#')
		// 		{
		// 			if (!serv->hasChannel(name))
		// 				return (cmd->queue(ERR_NOSUCHCHANNEL, name + " :No such channel"));
		// 			Channel*	chan = serv->getChannel(name);

		// 			if (!chan->isMember(cli))
		// 				return (cmd->queue(ERR_NOTONCHANNEL, chan->getName() + " :You're not on that channel"));
		// 			chan->rmClient(cli);
		// 		}
		// 	}
		// }

		// void	mode	(Command* cmd)
		// {
		// 	if (cmd->getArgC() < 1)
		// 		return (cmd->setResult(ERR_NEEDMOREPARAMS));
		// 	// std::cout << cmd->getArgs()[0] << "," << cmd->getArgs()[1] << std::endl;
		// 	const std::string&	targ = cmd->getArgs()[0];

		// 	// const std::string&	mstr = cmd->getArgs()[1];

		// 	if (targ[0] == '#' || targ[0] == '&') //channel mode
		// 	{
		// 		if (!cmd->getServer()->hasChannel(targ.c_str() + 1))
		// 			return (cmd->setResult(ERR_NOSUCHCHANNEL));
		// 		Channel*	channel = cmd->getServer()->getChannel(targ.c_str() + 1);
		// 		if (!channel->isMember(cmd->getClient()))
		// 			return (cmd->setResult(ERR_NOTONCHANNEL));

		// 		if (cmd->getArgC() > 1)
		// 		{
		// 			const std::string&	mstr = cmd->getArgs()[1];
		// 			std::string::const_iterator	it = mstr.begin();
		// 			char	ad = 0;
		// 			while (it != mstr.end())
		// 			{
		// 				if (*it == '-')
		// 					ad = 1;
		// 				else if (*it == '+')
		// 					ad = 2;
		// 				else if (ad && (*it == 'o' || *it == 'p' || *it == 's' || *it == 'i'
		// 							|| *it == 't' || *it == 'n' || *it == 'b' || *it == 'v'))
		// 				{
		// 					if (ad == 1)
		// 						channel->unsetMode(*it);
		// 					else
		// 						channel->setMode(*it);
		// 				}
		// 				else
		// 					return (cmd->setResult(ERR_UNKNOWNCOMMAND));
		// 				++it;
		// 			}
		// 		}

		// 		return (cmd->setResult(RPL_CHANNELMODEIS, "#" + channel->getName() + " +" + channel->getModestr()));
		// 	}
		// 	else // user mode
		// 	{
		// 		Client*	client = cmd->getServer()->getClient(targ);
		// 		if (!client)
		// 			return (cmd->setResult(ERR_NOSUCHNICK));

		// 		if (cmd->getArgC() > 1)
		// 		{
		// 			const std::string&	mstr = cmd->getArgs()[1];
		// 			std::string::const_iterator	it = mstr.begin();
		// 			char	ad = 0;
		// 			while (it != mstr.end())
		// 			{
		// 				if (*it == '-')
		// 					ad = 1;
		// 				else if (*it == '+')
		// 					ad = 2;
		// 				else if (ad && (*it == 'i' || *it == 's' || *it == 'w' || *it == 'o'))
		// 				{
		// 					if (ad == 1)
		// 						client->unsetMode(*it);
		// 					else
		// 						client->setMode(*it);
		// 				}
		// 				else
		// 					return (cmd->setResult(ERR_UNKNOWNCOMMAND));
		// 				++it;
		// 			}
		// 		}

		// 		std::cout << client->getNick() << " modes:[" << client->getModestr() << "]" << std::endl;
		// 		return (cmd->setResult(RPL_UMODEIS));
		// 	}
		// }

		// void	topic	(Command* cmd)
		// {
		// 	if (!cmd->getArgC())
		// 		cmd->setResult(ERR_NEEDMOREPARAMS);
		// 	const std::string&	name = cmd->getArgs()[0];
		// 	if (!cmd->getServer()->hasChannel(name))
		// 		return (cmd->setResult(ERR_NOSUCHCHANNEL));

		// 	Channel*		channel = cmd->getServer()->getChannel(name);
		// 	if (channel->getTopic().empty())
		// 		return (cmd->setResult(RPL_NOTOPIC));
		// 	return (cmd->setResult(RPL_TOPIC, channel->getTopic()));
		// }

		// void	names	(Command* cmd)
		// {

		// }

		// void	list	(Command* cmd)
		// {
		// 	// std::cout << "LIST CALLED" << cmd->getArgC() << std::endl;
		// 	// std::cout << cmd->getArgs()[0] << "#" << std::endl;
		// 	if (cmd->getArgC() > 1)
		// 		cmd->setResult(ERR_NOSUCHSERVER); // we dun know any servers.

		// 	if (!cmd->getArgC()) // list all channels
		// 	{
		// 		const Server::channels_t&	channels = cmd->getServer()->getChannels();
		// 		Server::channels_t::const_iterator	it = channels.begin();

		// 		while (it != channels.end())
		// 		{
		// 			Channel*	channel = it->second;
		// 			std::string	str = cmd->getServer()->getPrefix(cmd->getClient()) + to_string(RPL_LIST);
		// 			str += (" " + cmd->getClient()->getNick() + " ");
		// 			str += ("#" + channel->getName() + ":" + channel->getTopic());
		// 			cmd->getServer()->queue(cmd->getClient(), str);
		// 			++it;
		// 		}
		// 		cmd->setResult(RPL_LISTEND);
		// 	}
		// 	else
		// 	{

		// 	}
		// }

		// void	invite	(Command* cmd)
		// {
		// 	if (cmd->getArgC() < 2)
		// 		return (cmd->setResult(ERR_NEEDMOREPARAMS));

		// 	const std::string&	target = cmd->getArgs()[0];
		// 	const std::string&	chann = cmd->getArgs()[1];

		// 	Client*	client = cmd->getServer()->getClient(target);
		// 	if (!client)
		// 		return (cmd->setResult(ERR_NOSUCHNICK));
		// 	if (!cmd->getServer()->hasChannel(chann))
		// 		return (cmd->setResult(ERR_NOSUCHCHANNEL));
		// 	Channel*	channel = cmd->getServer()->getChannel(chann);
		// 	channel->inviteMember(client);
		// 	cmd->setResult(RPL_INVITING, "#" + channel->getName() + " " + client->getNick());
		// }

		// void	kick	(Command* cmd)
		// {

		// }
	}
}
