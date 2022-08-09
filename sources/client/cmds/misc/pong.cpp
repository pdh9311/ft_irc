#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <ctime>

void	irc::cmd::pong	(irc::Command* cmd)
{
	const std::string&	sender = cmd->getTrailing();
	Client*	cli = cmd->getClient();

	if (sender.empty())
		return (cmd->queue(ERR_NOORIGIN));
	cli->setLastPing(std::time(0));
}
