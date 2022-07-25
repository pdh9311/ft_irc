/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:11 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/25 16:10:47 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"

namespace irc
{
	namespace cmd
	{
		void	nick(Command* cmd)
		{
			// std::cout << "nick command called" << std::endl;
			// std::cout << "prefix:" << cmd->getPrefix() << std::endl;
			// std::cout << "command:" << cmd->getCommand() << std::endl;
			// std::vector<std::string>	args = cmd->getArgs();
			// for(int i = 0; i < args.size(); ++i)
			// 	std::cout << "arg#" << i << ":" << args[i] << std::endl;

			const std::string&	nick = cmd->getArgs()[0];

			if (!nick.size())
				return (cmd->setResult(ERR_NONICKNAMEGIVEN));
			if (nick.size() > 9 /* || check_nick_syntax */)
				return (cmd->setResult(ERR_ERRONEUSNICKNAME));

			const Server::clients_t&	clients = cmd->getServer()->getClients();
			Server::clients_t::const_iterator	it = clients.begin();

			while (it != clients.end())
			{
				if (it->second->getNick() == nick)
					return (cmd->setResult(ERR_NICKNAMEINUSE));
				++it;
			}
			// ERR_NICKCOLLISION? check if it's S2S

			cmd->getClient()->setNick(cmd->getArgs()[0]);
		}
		
		void	user(Command* cmd)
		{
			std::cout << "user command called" << std::endl;
			std::cout << "result will be set to 001 (RPL_WELCOME) for now" << std::endl;
			std::string	ret = ":localhost 001 " + cmd->getClient()->getNick();
			cmd->setResult(ret);
		}
		
		void	server(Command* cmd)
		{
			
		}
		
		void	oper(Command* cmd)
		{
			
		}
		
		void	quit(Command* cmd)
		{
			// need to broadcast arg[0], the quit message
			cmd->getServer()->rmclient(cmd->getClient());
		}
		
		void	squit(Command* cmd)
		{
			
		}
	}
}