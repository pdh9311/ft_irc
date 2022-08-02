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
		/*
			Command: PASS
			Parameters: <password>
			Example:
				PASS <password>
			Numeric Replies:
				ERR_NEEDMOREPARAMS
				ERR_ALREADYREGISTRED
		 */
		void	pass(Command* cmd)
		{
			std::cout << "password" << std::endl;
			Server*		server = cmd->getServer();
			std::string	msg;

			if (cmd->getArgC() < 1)
			{
				cmd->queue(ERR_NEEDMOREPARAMS);
				return ;
			}
			const std::string&	pwd = cmd->getArgs()[0];

			std::cout << pwd << std::endl;

			if (cmd->getClient()->isLoggedIn())
			{
				msg = ":You may not reregister";
				cmd->queue(ERR_ALREADYREGISTRED, msg);
				return ;
			}
			if (pwd == server->getPass())	// if (pwd == "TODO:: PASSWORD")
			{
				std::cout << "test" << std::endl;
				cmd->getClient()->setStatus(Client::AUTH);
			}
			else // is this needed?
				cmd->getClient()->setStatus(Client::PENDING);
		}

		/*
			Command: NICK
			Parameters: <nickname> [ <hopcount> ]
			Example:
				NICK Wiz
					; 새로운 닉네임 "위즈"를 소개합니다.
				:WiZ NICK Kilroy
					; WiZ는 닉네임을 킬로이로 변경했습니다.
			Numeric Replies:
				ERR_NONICKNAMEGIVEN
				ERR_ERRONEUSNICKNAME
				ERR_NICKNAMEINUSE
				ERR_NICKCOLLISION
		*/
		// <nick>       ::= <letter> { <letter> | <number> | <special> }
		void	nick(Command* cmd)
		{
			std::string	msg;

			if (cmd->getArgC() < 1)
			{
				msg = ":No nickname given";
				cmd->queue(ERR_NONICKNAMEGIVEN, msg);	// no arg
				return ;
			}

			const std::string&	nick = cmd->getArgs()[0];
			if (!nick.size())
			{
				msg = ":No nickname given";
				cmd->queue(ERR_NONICKNAMEGIVEN, msg);	// no nick
				return ;
			}

			if (nick.size() > 9 || !isNickStr(nick))
			{
				msg = nick + " :Erroneus nickname";
				cmd->queue(ERR_ERRONEUSNICKNAME, msg);
				return ;
			}

			const Server::clients_t&			clients = cmd->getServer()->getClients();
			Server::clients_t::const_iterator	it = clients.begin();
			while (it != clients.end())
			{
				if (it->second->getNick() == nick)
				{
					msg = nick + " :Nickname is already in use";
					cmd->queue(ERR_NICKNAMEINUSE, msg);
					return ;
				}
				++it;
			}
			// ERR_NICKCOLLISION? check if it's S2S
			cmd->getClient()->setNick(cmd->getArgs()[0]);
		}

		/*
			Command: USER
			Parameters: <username> <hostname> <servername> <realname>
			Example:
				USER guest tolmoon tolsun :Ronnie Reagan
					; "guest"라는 사용자 이름과 실명 "Ronnie Reagan"으로 자신을 등록하는 사용자.
			Numeric Replies:
				ERR_NEEDMOREPARAMS
				ERR_ALREADYREGISTRED
		*/
		void	user(Command* cmd)
		{
			Server*		server = cmd->getServer();
			std::string	msg;

			if (cmd->getArgC() < 4)
			{
				cmd->queue(ERR_NEEDMOREPARAMS);
				return ;
			}

			const std::string&	username = cmd->getArgs()[0];
			const std::string&	realname = cmd->getArgs()[3];

			const Server::clients_t&			clients = cmd->getServer()->getClients();
			Server::clients_t::const_iterator	it = clients.begin();

			while (it != clients.end())
			{
				if (it->second->getUserName() == username)
				{
					msg = ":You may not reregister";
					cmd->queue(ERR_ALREADYREGISTRED, msg);
					return ;
				}
				++it;
			}

			Client*	client = cmd->getClient();
			client->setUserName(username);
			client->setRealName(realname);
			client->setStatus(Client::LOGGEDIN);
			msg = "Welcome to the Internet Relay Network ";
			msg += client->getNick() + "!" + client->getUserName() + "@" + server->getName();
			cmd->queue(RPL_WELCOME, msg);
			motd(cmd);
		}

		void	server(Command* cmd)
		{
			(void)cmd;
		}

		void	oper(Command* cmd)
		{
			(void)cmd;
		}

		void	quit(Command* cmd)
		{
			// need to broadcast arg[0], the quit message
			cmd->getServer()->rmClient(cmd->getClient());
		}

		void	squit(Command* cmd)
		{
			(void)cmd;
		}
	}
}
