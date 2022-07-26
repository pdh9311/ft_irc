/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:02 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/26 14:42:43 by minsunki         ###   ########seoul.kr  */
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
		void	join	(Command* cmd) // irssi seems to only support up to 2 channes per join message
		{
			int	argc = cmd->getArgC();
			if (!argc)
				return (cmd->setResult(ERR_NEEDMOREPARAMS));
			
			for (int i = 0; i < MAX_PARAMS; ++i)
			{
				const std::string&	cur = cmd->getArgs()[i];
				if (cur[0] != '#')
					break ;
				Channel*	channel = cmd->getServer()->getChannel(cur.c_str() + 1);
				channel->addClient(cmd->getClient());
				return (cmd->setResult(RPL_TOPIC));
			}
		}

		void	part	(Command* cmd)
		{

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