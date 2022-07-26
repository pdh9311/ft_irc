/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:02 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/26 16:23:15 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "channel/Channel.hpp"

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
			std::cout <<"_split " << str <<std::endl;
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
			bool	hasKeys = (cmd->getArgC() > 1);

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
					// set cchan
				}
			}

			std::cout << "current channel#: " << cmd->getServer()->getChannels().size() << std::endl;

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
			std::cout << "current channel#: " << cmd->getServer()->getChannels().size() << std::endl;
		}
		
		void	mode	(Command* cmd)
		{

		}

		void	topic	(Command* cmd)
		{

		}

		void	names	(Command* cmd)
		{

		}

		void	list	(Command* cmd)
		{

		}
		
		void	invite	(Command* cmd)
		{

		}

		void	kick	(Command* cmd)
		{

		}
	}
}