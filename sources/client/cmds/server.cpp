#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <vector>
#include <fstream>
#include <ctime>

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
			Server*						server = cmd->getServer();
			std::vector<std::string>	args = cmd->getArgs();
			std::string					msg;

			if (args.size() != 0)
			{
				msg = args[0];
				msg += " :No such server";
				cmd->queue(ERR_NOSUCHSERVER, msg);
				return ;
			}
			msg = ": Three are ";
			msg+= toString(server->getClients().size());	// TODO
			msg += " and <integer> services on 1 servers";
			cmd->queue(RPL_LUSERCLIENT, msg);

			msg =  "<integer> :operator(s) online";	// TODO
			cmd->queue(RPL_LUSEROP, msg);

			msg = "<integer> :unknown connection(s)";	// TODO
			cmd->queue(RPL_LUSERUNKNOWN, msg);

			msg = server->getChannels().size();
			msg += " :channels formed";
			cmd->queue(RPL_LUSERCHANNELS, msg);

			msg = ":I have ";
			msg += toString(server->getClients().size());	// TODO
			msg += " clients and 1 servers";
			cmd->queue(RPL_LUSERME, msg);
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
			Server*						server = cmd->getServer();
			std::vector<std::string>	args = cmd->getArgs();
			std::string					msg;

			if (args.size() != 0)
			{
				msg = args[0];
				msg += " :No such server";
				cmd->queue(ERR_NOSUCHSERVER, msg);
				return ;
			}
			msg = "version 0.0.1.<debuglevel> ";	// TODO
			msg += server->getName();
			msg += " :ft_irc server (Member: donpark, sunbchoi, minsunki)";
			cmd->queue(RPL_VERSION, msg);
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
			Server*						server = cmd->getServer();
			std::vector<std::string>	args = cmd->getArgs();
			std::string					msg;

			if (args.size() != 0)
			{
				msg = args[0];
				msg += " :No such server";
				cmd->queue(ERR_NOSUCHSERVER, msg);
				return ;
			}
			time_t	t = std::time(0);
			char buf[100];

			std::strftime(buf, sizeof(buf), "%c\n", localtime(&t));
			msg = server->getName();
			msg += " :";
			msg += buf;
			cmd->queue(RPL_TIME, msg);
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
			Server*						server = cmd->getServer();
			std::vector<std::string>	args = cmd->getArgs();
			std::string					msg;

			if (args.size() != 0)
			{
				msg = args[0];
				msg += " :No such server";
				cmd->queue(ERR_NOSUCHSERVER, msg);
				return ;
			}

			msg = server->getName();
			msg += " :Administrative info";
			cmd->queue(RPL_ADMINME, msg);

			msg = "Member: donpark, sunbchoi, minsunki";
			cmd->queue(RPL_ADMINLOC1, msg);

			msg = "Name: Donghyeon Park, Sunbin Choi, Minsung Kim";
			cmd->queue(RPL_ADMINLOC2, msg);

			msg = "Email:\n";
			msg += "- donpark@student.42seoul.kr\n";
			msg += "- sunbchoi@student.42seoul.kr\n";
			msg += "- minsunki@student.42seoul.kr";
			cmd->queue(RPL_ADMINEMAIL, msg);
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
			std::vector<std::string>	args = cmd->getArgs();
			std::string					msg;

			if (args.size() != 0)
			{
				msg = args[0];
				msg += " :No such server";
				cmd->queue(ERR_NOSUCHSERVER, msg);
				return ;
			}

			msg = "FT_IRC : donpark, sunbchoi, minsunki";
			cmd->queue(RPL_INFO, msg);

			msg = ":End of INFO list";
			cmd->queue(RPL_ENDOFINFO, msg);

		}
	}
}
