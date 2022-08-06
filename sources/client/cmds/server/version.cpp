#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

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
void	irc::cmd::version	(irc::Command* cmd)
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
	msg = "version 0.0.1 ";
	msg += server->getName();
	msg += " :ft_irc server (Member: donpark, sunbchoi, minsunki)";
	cmd->queue(RPL_VERSION, msg);
}
