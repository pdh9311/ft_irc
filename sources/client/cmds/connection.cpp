/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:11 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/28 14:51:44 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

namespace irc
{
	namespace cmd
	{
		void	pass(Command* cmd)
		{
			if (cmd->getArgC() < 1)
				return (cmd->setResult(ERR_NEEDMOREPARAMS));
			const std::string&	pwd = cmd->getArgs()[0];

			if (cmd->getClient()->isLoggedIn())
				return (cmd->setResult(ERR_ALREADYREGISTRED));
			
			if (pwd == "TODO:: PASSWORD")
				cmd->getClient()->setStatus(Client::AUTH);
			else // is this needed?
				cmd->getClient()->setStatus(Client::PENDING);
		}
		
		void	nick(Command* cmd)
		{
			// std::cout << "nick command called" << std::endl;
			// std::cout << "prefix:" << cmd->getPrefix() << std::endl;
			// std::cout << "command:" << cmd->getCommand() << std::endl;
			// std::vector<std::string>	args = cmd->getArgs();
			// for(int i = 0; i < args.size(); ++i)
			// 	std::cout << "arg#" << i << ":" << args[i] << std::endl;

			if (cmd->getArgC() < 1)
				return (cmd->setResult(ERR_NONICKNAMEGIVEN)); // no arg, no nick
			const std::string&	nick = cmd->getArgs()[0];
			
			if (!nick.size())
				return (cmd->setResult(ERR_NONICKNAMEGIVEN));
			if (nick.size() > 9 || !isNickStr(nick))
				return (cmd->setResult(ERR_ERRONEUSNICKNAME));

			const Server::clients_t&			clients = cmd->getServer()->getClients();
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
			// std::cout << "user command called" << std::endl;
			// std::cout << "result will be set to 001 (RPL_WELCOME) for now" << std::endl;
			// std::string	ret = ":localhost 001 " + cmd->getClient()->getNick();
			// cmd->setResult(ret);
			if (cmd->getArgC() < 4)
				cmd->setResult(ERR_NEEDMOREPARAMS);

			const std::string&	username = cmd->getArgs()[0];
			const std::string&	realname = cmd->getArgs()[3];

			const Server::clients_t&	clients = cmd->getServer()->getClients();
			Server::clients_t::const_iterator it = clients.begin();

			while (it != clients.end())
			{
				if (it->second->getUserName() == username)
					cmd->setResult(ERR_ALREADYREGISTRED);
				++it;
			}
			
			Client*	client = cmd->getClient();
			client->setUserName(username);
			client->setRealName(realname);
			// cmd->getServer()->welcome(client);
			client->setStatus(Client::LOGGEDIN);
			cmd->setResult(RPL_WELCOME, client->getNick());
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