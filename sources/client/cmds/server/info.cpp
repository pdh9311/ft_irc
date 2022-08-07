#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

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
void	irc::cmd::info	(irc::Command* cmd)
{
	std::string	msg;

	if (cmd->getArgC() != 0)
	{
		msg = cmd->getArgs()[0];
		msg += " :No such server";
		cmd->queue(ERR_NOSUCHSERVER, msg);
		return ;
	}

	msg = "FT_IRC : donpark, sunbchoi, minsunki";
	cmd->queue(RPL_INFO, msg);

	msg = ":End of INFO list";
	cmd->queue(RPL_ENDOFINFO, msg);

}
