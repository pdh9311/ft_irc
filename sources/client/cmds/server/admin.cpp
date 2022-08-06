#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

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
void	irc::cmd::admin	(irc::Command* cmd)
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
