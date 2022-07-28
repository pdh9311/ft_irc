/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:02 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/28 15:26:51 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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

		static const std::vector<std::string>	_split(const std::string& str)
		{
			// std::cout <<"_split " << str <<std::endl;
			std::vector<std::string>	ret;
			size_t						cur = 0;
			size_t						fpos = cur;
			
			if (str.empty())
				return (ret);

			while (1)
			{
				fpos = str.find(',', cur);
				std::string	token = str.substr(cur, fpos - cur);
				ret.push_back(token);
				if (fpos == std::string::npos)
					break ;
				cur = fpos + 1;
			}
			
			return (ret);
		}
		
		void	join	(Command* cmd) 
		{
			// bool	hasKeys = (cmd->getArgC() > 1);

			if (cmd->getArgs().empty())
				return (cmd->setResult(ERR_NEEDMOREPARAMS));
			
			const std::vector<std::string>	servers = _split(cmd->getArgs()[0]);
			// const std::vector<std::string>	keys = (cmd->getArgC() > 1 ? _split(cmd->getArgs()[1]) : )
			
			for (size_t i = 0; i < servers.size(); ++i)
			{
				const std::string&	name = servers[i];
				if (name[0] == '#')
				{
					Channel*	channel = cmd->getServer()->getChannel(name.c_str() + 1);
					channel->addClient(cmd->getClient());
					cmd->getClient()->setCChannel(channel);
				}
			}
			
			const Channel*	channel = cmd->getClient()->getCChannel();
			if (channel && !channel->getTopic().empty())
				cmd->setResult(RPL_NOTOPIC);

			// return (cmd->setResult(RPL_TPOIC, cmd->getUser->getCChannel()->getTopic()));
			// size_t	cur = 0;
			// size_t	fpos = cur;

			// while ((fpos = servers.find(',', cur)) != std::string::npos)
			// {
			// 	std::string	name = servers.substr(cur, fpos - cur);
			// 	std::cout << "name: " << name << std::endl;
			// 	if (name[0] == '#')
			// 	{
			// 		Channel*	channel = cmd->getServer()->getChannel(name.c_str() + 1);
			// 		channel->addClient(cmd->getClient());
			// 		// set client's cchan to channel
			// 	}
			// 	cur = fpos;
			// }

			// cur = 0;
			// fpos = cur;

			// while ((fpos = ))
			// for (int i = 0; i < MAX_PARAMS; ++i)
			// {
			// 	const std::string&	cur = cmd->getArgs()[i];
			// 	if (cur[0] != '#')
			// 		break ;
			// 	Channel*	channel = cmd->getServer()->getChannel(cur.c_str() + 1);
			// 	channel->addClient(cmd->getClient());
			// 	return (cmd->setResult(RPL_TOPIC));
			// }
		}

		void	part	(Command* cmd)
		{
			if (cmd->getArgs().empty())
				return (cmd->setResult(ERR_NEEDMOREPARAMS));
			
			const std::vector<std::string>	servers = _split(cmd->getArgs()[0]);

			for (size_t i = 0; i < servers.size(); ++i)
			{
				const std::string&	name = servers[i];
				if (name[0] == '#')
				{
					if (!cmd->getServer()->hasChannel(name.c_str() + 1))
						return (cmd->setResult(ERR_NOSUCHCHANNEL));
					
					Channel*	channel = cmd->getServer()->getChannel(name.c_str() + 1);

					if (!channel->isMember(cmd->getClient()))
						return (cmd->setResult(ERR_NOTONCHANNEL));
					channel->rmClient(cmd->getClient());
				}
			}
		}
		
		void	mode	(Command* cmd)
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

		void	topic	(Command* cmd)
		{
			if (!cmd->getArgC())
				cmd->setResult(ERR_NEEDMOREPARAMS);
			const std::string&	name = cmd->getArgs()[0];
			if (!cmd->getServer()->hasChannel(name))
				return (cmd->setResult(ERR_NOSUCHCHANNEL));

			Channel*		channel = cmd->getServer()->getChannel(name);
			if (channel->getTopic().empty())
				return (cmd->setResult(RPL_NOTOPIC));
			return (cmd->setResult(RPL_TOPIC, channel->getTopic()));
		}

		void	names	(Command* cmd)
		{

		}

		void	list	(Command* cmd)
		{
			// std::cout << "LIST CALLED" << cmd->getArgC() << std::endl;
			// std::cout << cmd->getArgs()[0] << "#" << std::endl;
			if (cmd->getArgC() > 1)
				cmd->setResult(ERR_NOSUCHSERVER); // we dun know any servers.
			
			if (!cmd->getArgC()) // list all channels
			{
				const Server::channels_t&	channels = cmd->getServer()->getChannels();
				Server::channels_t::const_iterator	it = channels.begin();

				while (it != channels.end())
				{
					Channel*	channel = it->second;
					std::string	str = cmd->getServer()->getPrefix(cmd->getClient()) + to_string(RPL_LIST);
					str += (" " + cmd->getClient()->getNick() + " ");
					str += ("#" + channel->getName() + ":" + channel->getTopic());
					cmd->getServer()->queue(cmd->getClient(), str);
					++it;
				}
				cmd->setResult(RPL_LISTEND);
			}
			else
			{

			}
		}
		
		void	invite	(Command* cmd)
		{
			if (cmd->getArgC() < 2)
				return (cmd->setResult(ERR_NEEDMOREPARAMS));
			
			const std::string&	target = cmd->getArgs()[0];
			const std::string&	chann = cmd->getArgs()[1];

			Client*	client = cmd->getServer()->getClient(target);
			if (!client)
				return (cmd->setResult(ERR_NOSUCHNICK));
			if (!cmd->getServer()->hasChannel(chann))
				return (cmd->setResult(ERR_NOSUCHCHANNEL));
			Channel*	channel = cmd->getServer()->getChannel(chann);
			channel->inviteMember(client);
			cmd->setResult(RPL_INVITING, "#" + channel->getName() + " " + client->getNick());
		}

		void	kick	(Command* cmd)
		{

		}
	}
}