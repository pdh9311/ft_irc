#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

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
void	irc::cmd::away	(irc::Command* cmd)
{
	(void)cmd;
}
