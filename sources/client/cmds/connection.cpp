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
			if (cmd->getClient()->isLoggedIn())
			{
				msg = ":Unauthorized command (already registered)";
				cmd->queue(ERR_ALREADYREGISTRED, msg);
				return ;
			}
			const std::string&	pwd = cmd->getArgs()[0];
			if (pwd == server->getPass())
				cmd->getClient()->setStatus(Client::AUTH);
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
		void	nick(Command* cmd)
		{
			Server*	server = cmd->getServer();
			std::string	msg;
			const std::string&	nick = cmd->getArgs()[0];

			if (cmd->getArgC() < 1)
			{
				msg = ":No nickname given";
				cmd->queue(ERR_NONICKNAMEGIVEN, msg);	// no arg
				return ;
			}

			if (!nick.size())
			{
				msg = ":No nickname given";
				cmd->queue(ERR_NONICKNAMEGIVEN, msg);	// no nick
				return ;
			}

			if (nick.size() > 9 || !isNickStr(nick))
			{
				msg = ":Erroneus nickname";
				cmd->queue(ERR_ERRONEUSNICKNAME, msg);
				return ;
			}

			const Server::clients_t&			clients = cmd->getServer()->getClients();
			Server::clients_t::const_iterator	it = clients.begin();
			Client* client = cmd->getClient();
			while (it != clients.end())
			{
				if (it->second->getNick() == nick)
				{
					msg = ": ";
					msg = to_string(ERR_NICKNAMEINUSE) + " * ";
					msg += nick + " :Nickname is already in use";
					cmd->queue(msg);
					return ;
				}
				++it;
			}
			// ERR_NICKCOLLISION? check if it's S2S

			client->setNick(nick);
			if (client->getPastName().empty())
				client->setPastName(nick);
			// msg = ": NICK :" + cmd->getArgs()[0];
			// cmd->queue(msg);
			msg = ":";
			if (client->getWelcome() == true)
			{
				msg += client->getPastName(); + "!" + client->getUserName() + "@" + server->getName();
				client->setPastName(client->getNick());
			}
			msg += " NICK :" + cmd->getArgs()[0];
			cmd->queue(msg);
			if (client->getStatus() == Client::LOGGEDIN && client->getWelcome() == 0)
			{
				msg = ":Welcome to the Internet Relay Network ";
				msg += client->getNick() + "!" + client->getUserName() + "@" + cmd->getServer()->getName();
				cmd->queue(RPL_WELCOME, msg);

				motd(cmd);
				client->setWelcome(1);

				// 직접 whois 응답 비슷하게 임의로 만들어서 넣어주는 방식..
				// > :ubuntu_!ubuntu@localhost 221 ubuntu_ +wi
				// > :ubuntu_!ubuntu@localhost 311 ubuntu_ ubuntu ubuntu localhost * :Ubuntu
				// > :ubuntu_!ubuntu@localhost 318 ubuntu_ ubuntu :End of /WHOIS list
				// msg = ":" + client->getNick() + "!" + client->getUserName() + "@" + server->getName() + " 221 " + client->getNick() + " +wi";
				// cmd->queue(msg);
				// msg = ":" + client->getNick() + "!" + client->getUserName() + "@" + server->getName() + " 331 " + client->getNick() + " ";
				// msg += client->getUserName() + " " + client->getUserName() + " " + server->getName() + " * :donpark";
				// cmd->queue(msg);
				// msg = ":" + client->getNick() + "!" + client->getUserName() + "@" + server->getName() + " 338 " + client->getNick() + " ";
				// msg += client->getUserName() + ":End of /WHOIS list";
				// cmd->queue(msg);

				// TODO 직접 다시 nick 메시지 보내서 그냥 해결....... whois 응답 필요
				msg = ":" + client->getPastName() + "!" + client->getUserName() + "@" + server->getName();
				msg += " NICK :" + cmd->getArgs()[0];
				cmd->queue(msg);
				client->setPastName(client->getNick());
			}
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

			if (cmd->getArgC() < 3) // 1 is trailing
			{
				cmd->queue(ERR_NEEDMOREPARAMS);
				return ;
			}

			const std::string&	username = cmd->getArgs()[0];
			const std::string&	realname = cmd->getArgs()[3];

			if (cmd->getClient()->isLoggedIn())
			{
				msg = ":" + cmd->getClient()->getNick() + "!" + username + "@" + cmd->getServer()->getName() + " ";
				msg += to_string(ERR_ALREADYREGISTRED) + " ";
				msg += username + " :Unauthorized command (already registered)";
				cmd->queue(msg);
				return ;
			}

			Client*	client = cmd->getClient();
			client->setUserName(username);
			client->setRealName(realname);
			client->setStatus(Client::LOGGEDIN);
			if (!client->getNick().empty())
			{
				client->setWelcome(true);
				msg = ":Welcome to the Internet Relay Network ";
				msg += client->getNick() + "!" + client->getUserName() + "@" + server->getName();
				cmd->queue(RPL_WELCOME, msg);

				motd(cmd);
			}
		}

		void	server(Command* cmd)
		{
			(void)cmd;
		}

		void	oper(Command* cmd)
		{
			if (cmd->getArgC() < 2)
				cmd->queue(ERR_NEEDMOREPARAMS);

			Server*				serv = cmd->getServer();
			Client*				cli = cmd->getClient();
			const std::string&	oper_nick = serv->conf.get_O().getNickname();
			const std::string&	oper_pwd = serv->conf.get_O().getPassword();

			if (oper_nick.empty() || oper_pwd.empty())
				cmd->queue(ERR_NOOPERHOST, ":No O-lines for your host");

			const std::string&	nick = cmd->getArgs()[0];
			const std::string&	pwd = cmd->getArgs()[1];

			if (nick != oper_nick)
				return ;
			if (pwd != oper_pwd)
				return (cmd->queue(ERR_PASSWDMISMATCH, ":Password Incorrect"));
			cmd->queue(RPL_YOUREOPER, ":You are now an IRC operator");
			cli->setMode('o');
			cmd->queue(RPL_UMODEIS, "+ " + cli->getModestr());
		}

		void	quit(Command* cmd)
		{
			// need to broadcast arg[0], the quit message
			cmd->getServer()->rmClient(cmd->getClient());
		}

		void	squit(Command* cmd)
		{
			if (cmd->getArgC() < 2)
				return ;
			Server*	serv = cmd->getServer();
			Client*	cli = cmd->getClient();
			const std::string&	name = cmd->getArgs()[0];

			if (!cli->hasMode('o'))
				return (cmd->queue(ERR_NOPRIVILEGES));
			return (cmd->queue(ERR_NOSUCHSERVER, name + " :No such server"));

			// cmd->queue(ERR_NOSUCHSERVER, "")
		}
	}
}
