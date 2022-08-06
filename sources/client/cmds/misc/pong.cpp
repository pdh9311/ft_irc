#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <ctime>

void	irc::cmd::pong	(irc::Command* cmd)
{
	const std::string& a1 = cmd->getArgs()[0];
	if (a1.empty())
		return (cmd->setResult(ERR_NOORIGIN));
	cmd->getClient()->setLastPing(std::time(0)); // does pong arg have to match nick?
}
