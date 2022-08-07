#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <ctime>

void	irc::cmd::ping	(irc::Command* cmd)
{
	// client should not call ping command. Ignore? nvm, irssi sends ping
	if (cmd->getArgC() < 1)
		return ; // ping won't send ERR_NEEDMOREPARAMS
	const std::string&	targ = cmd->getArgs()[0];
	if (cmd->getClient()->getNick() == targ)
		cmd->getServer()->queue(cmd->getClient()->getFD(),
			cmd->getServer()->getPrefix(cmd->getClient()) + " PONG " + targ);
}
