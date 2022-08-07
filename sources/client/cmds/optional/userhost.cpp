#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

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
void	irc::cmd::userhost	(irc::Command* cmd)
{
	(void)cmd;
}
