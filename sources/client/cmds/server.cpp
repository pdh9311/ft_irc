#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"
#include <fstream>

namespace irc
{
	namespace cmd
	{
		/*
			Command: MOTD
			Parameters: [ <target> ]
			Numeric Replies:
				RPL_MOTDSTART
				RPL_MOTD
				RPL_ENDOFMOTD
				ERR_NOMOTD
		*/
		void	motd	(Command* cmd)
		{
			Server*		server = cmd->getServer();
			Client*		client = cmd->getClient();

			std::string	msg;

			msg = ":- " + server->getName() + " Message of the day - ";
			cmd->queue(RPL_MOTDSTART, msg);

			std::ifstream	file("motd.txt");
			char			buf[510];
			if (!file.is_open())
			{
				msg = ":MOTD File is missing";
				cmd->queue(ERR_NOMOTD, msg);
				return ;
			}
			while (!file.eof())
			{
				file.getline(buf, sizeof(buf));
				msg = ": - ";
				msg += buf;
				cmd->queue(RPL_MOTD, msg);
			}
			msg = ":End of MOTD command";
			cmd->queue(RPL_ENDOFMOTD, msg);
		}

		/*
			Command: LUSERS
			Parameters: [ <mask> [ <target> ] ]
			Numeric Replies:
				RPL_LUSERCLIENT
				RPL_LUSEROP
				RPL_LUSERUNKOWN
				RPL_LUSERCHANNELS
				RPL_LUSERME
				ERR_NOSUCHSERVER
		*/
		void	lusers	(Command* cmd)
		{

		}

		/*
			Command: VERSION
			Parameters: [<server>]
			Example:
				:Wiz VERSION *.se
					; "*.se"와 일치하는 서버의 버전을 확인하라는 Wiz의 메시지
				VERSION tolsun.oulu.fi
					; "tolsun.oulu.fi" 서버의 버전을 확인하십시오.
			Numeric Replies:
				ERR_NOSUCHSERVER
				RPL_VERSION
		*/
		void	version	(Command* cmd)
		{

		}

		void	stats	(Command* cmd)
		{

		}

		void	links	(Command* cmd)
		{

		}

		/*
			Command: TIME
			Parameters: [<server>]
			Example:
				TIME tolsun.oulu.fi
					; "tolson.oulu.fi" 서버의 시간을 확인하십시오.
				Angel TIME *.au
					; "*.au"와 일치하는 서버의 시간을 확인하는 user angel
			Numeric Replies:
				ERR_NOSUCHSERVER
				RPL_TIME
		*/
		void	time	(Command* cmd)
		{

		}

		void	connect	(Command* cmd)
		{

		}

		void	trace	(Command* cmd)
		{

		}

		/*
			Command: ADMIN
			Parameters: [<server>]
			Example:
				ADMIN tolsun.oulu.fi
					; tolsun.oulu.fi에서 ADMIN 응답 요청
				:WiZ ADMIN *.edu
					; *.edu와 일치하는 첫 번째 서버에 대한 WiZ의 ADMIN 요청.
			Numeric Replies:
				ERR_NOSUCHSERVER
				RPL_ADMINME
				RPL_ADMINLOC1
				RPL_ADMINLOC2
				RPL_ADMINEMAIL
		*/
		void	admin	(Command* cmd)
		{

		}

		/*
			Command: INFO
			Parameters: [<server>]
			Example:
				INFO csd.bu.edu
					; csd.bu.edu에서 정보 회신 요청
				:Avalon INFO *.fi
					; *.fi와 일치하는 첫 번째 서버에 대한 Avalon의 정보 요청.
				INFO Angel
					; Angel이 연결된 서버에서 정보를 요청합니다.
			Numeric Replies:
				ERR_NOSUCHSERVER
				RPL_INFO
				RPL_ENDOFINFO
		*/
		void	info	(Command* cmd)
		{

		}
	}
}
