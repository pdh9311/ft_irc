#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <ctime>

void	irc::cmd::ping	(irc::Command* cmd)
{
	if (cmd->getArgC() < 1)
		return (cmd->queue(ERR_NOORIGIN));
	const std::string&	sender = cmd->getArgs()[0];
	
	cmd->queue("PONG :" + sender);	
}
