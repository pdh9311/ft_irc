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
			Command: AWAY
			Parameters: [message]
			Example:
				AWAY :Gone to lunch.  Back in 5
					; 메시지를 "점심 먹으러 갔다. 5시에 돌아오라"로 설정합니다.
				:WiZ AWAY
					; WiZ를 부재중으로 표시 해제합니다.
			Numeric Replies:
				RPL_UNAWAY
				RPL_NOWAWAY
		*/
		void	away	(Command* cmd)
		{
			(void)cmd;
		}

		void	rehash	(Command* cmd)
		{
			(void)cmd;
		}

		void	restart	(Command* cmd)
		{
			(void)cmd;
		}

		void	summon	(Command* cmd)
		{
			(void)cmd;
		}

		void	users	(Command* cmd)
		{
			(void)cmd;
		}

		void	wallops	(Command* cmd)
		{
			(void)cmd;
		}

		bool is_exsit_client(Server::clients_t clients, std::string nick)
		{
			Server::clients_t::iterator it;

			for (it = clients.begin(); it != clients.end(); it++)
			{
				if (((*it).second)->getNick() == nick)
					return (true);
			}
			return (false);
		}

		/*
			Command: USERHOST
			Parameters: <nickname>{<space><nickname>}
			Example:
				USERHOST Wiz Michael Marty p
					;USERHOST는 "Wiz", "Michael", "Marty" 및 "p"라는 별명에 대한 정보를 요청합니다.
			Numeric Replies:
				RPL_USERHOST
				ERR_NEEDMOREPARAMS
		*/
		// RPL_USERHOST
        //    ":[<reply>{<space><reply>}]"
        // - 쿼리 목록에 대한 응답을 나열하기 위해 USERHOST에서 사용하는 응답 형식입니다.
		//   응답 문자열은 다음과 같이 구성됩니다.:
		//   reply = nickname [ "*" ] "=" ( "+" / "-" ) hostname
        //   '*'는 클라이언트가 운영자로 등록되었는지 여부를 나타냅니다.
		//   '-' 또는 '+' 문자는 각각 클라이언트가 AWAY 메시지를 설정했는지 여부를 나타냅니다.
		void	userhost	(Command* cmd)
		{
			(void)cmd;
			// Server*						server = cmd->getServer();
			// std::string					msg;
			// std::vector<std::string>	nicks = split(cmd->getArgs()[0], ' ');
			// Server::clients_t			clients = server->getClients();
			// Server::clients_t::iterator	cliter;

			// if (cmd->getArgC() == 0)
			// {
			// 	cmd->queue(ERR_NEEDMOREPARAMS);
			// 	return ;
			// }
			// size_t	count = nicks.size();
			// if (nicks.size() > 5)
			// 	count = 5;
			// for (size_t i = 0; i < count; i++)
			// {
			// 	// 클라이언트가 존재하는지
			// 	// 존재하면 운영자인지, away 상태인지 판단.
			// }



		}

		/*
			Command: ISON
			Parameters: <nickname>{<space><nickname>}
			Example:
				ISON phone trillian WiZ jarlek Avalon Angel Monstah
					; 7개의 닉에 대한 샘플 ISON 요청.
			Numeric Replies:
				RPL_ISON
				ERR_NEEDMOREPARAMS
		*/
		void	ison	(Command* cmd)
		{
			Server*		server = cmd->getServer();
			std::string	msg;

			if (cmd->getArgC() == 0)
			{
				cmd->queue(ERR_NEEDMOREPARAMS);
				return ;
			}
			std::string					onicks = cmd->getArgs()[0].substr(1);
			std::vector<std::string>	nicks = irc::split(onicks, ' ');
			std::vector<std::string>	online;
			std::map<int, Client*>		clients = server->getClients();

			std::map<int, Client*>::iterator	it;
			for (it = clients.begin(); it != clients.end(); ++it)
			{
				std::vector<std::string>::iterator	nit;
				for (nit = nicks.begin(); nit != nicks.end(); ++nit)
				{
					if ((*it).second->getNick() == (*nit))
					{
						online.push_back((*it).second->getNick());
						break ;
					}
				}
			}
			if (online.size() == 0)
				msg = ":[]";
			else
			{
				msg = ":[";
				std::vector<std::string>::iterator oit;
				for (size_t i = 0; i < online.size(); i++)
				{
					msg += online[i];
					if (i != online.size() - 1)
						msg += " ";
				}
				msg += "]";
			}
			cmd->queue(RPL_ISON, msg);	// ":[<nick> {<space><nick>}]"
		}
	}
}
