#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <ctime>

namespace irc
{
	namespace cmd
	{
		void	kill	(Command* cmd)
		{
			std::string			msg;
			std::string 		user_str = cmd->getArgs()[0];
			
			if (cmd->getArgC() < 1 || cmd->getTrailing().length() == 1)
				return (cmd->setResult(ERR_NEEDMOREPARAMS));
			const Server::clients_t&			clients = cmd->getServer()->getClients();
			Server::clients_t::const_iterator	it = clients.begin();
			Client* client;
			while (it != clients.end())
			{
				if (it->second->getNick() == user_str)
					break;
				++it;
			}
			if (it == clients.end())
					return (cmd->setResult(ERR_NOSUCHNICK, user_str));	
			client = it->second;
			if (client->hasMode('o') == 0)
				return (cmd->setResult(ERR_NOPRIVILEGES));
			cmd->getServer()->rmClient(client); //실패시 ERR_CANTKILLSERVER 
			msg = cmd->getServer()->getPrefix(cmd->getClient()) + " KILL :" + cmd->getTrailing().substr(1);
			client->queue(msg);
			msg = cmd->getServer()->getPrefix(cmd->getClient()) + " QUIT :" + cmd->getTrailing().substr(1);
			client->queue(msg);
		}
		
		void	ping	(Command* cmd)
		{
			// client should not call ping command. Ignore? nvm, irssi sends ping
			if (cmd->getArgC() < 1)
				return ; // ping won't send ERR_NEEDMOREPARAMS
			const std::string&	targ = cmd->getArgs()[0];
			if (cmd->getClient()->getNick() == targ)
				cmd->getServer()->queue(cmd->getClient()->getFD(),
					cmd->getServer()->getPrefix(cmd->getClient()) + " PONG " + targ);
		}

		void	pong	(Command* cmd)
		{
			const std::string& a1 = cmd->getArgs()[0];
			if (a1.empty())
				return (cmd->setResult(ERR_NOORIGIN));
			cmd->getClient()->setLastPing(std::time(0)); // does pong arg have to match nick?
		}

		void	error	(Command* cmd)
		{
			(void)cmd;
		}
	}
}
