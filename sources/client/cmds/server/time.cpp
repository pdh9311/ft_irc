#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <ctime>

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
void	irc::cmd::time	(irc::Command* cmd)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;

	if (cmd->getArgC() != 0)
	{
		msg = cmd->getArgs()[0];
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
