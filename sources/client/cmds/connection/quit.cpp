#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

void	irc::cmd::quit(irc::Command* cmd)
{
	// need to broadcast arg[0], the quit message
	cmd->getServer()->rmClient(cmd->getClient());
}
