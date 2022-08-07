#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

void	irc::cmd::squit(irc::Command* cmd)
{
	if (cmd->getArgC() < 2)
		return ;
	// Server*	serv = cmd->getServer();
	irc::Client*		cli = cmd->getClient();
	const std::string&	name = cmd->getArgs()[0];

	if (!cli->hasMode('o'))
		return (cmd->queue(ERR_NOPRIVILEGES));
	return (cmd->queue(ERR_NOSUCHSERVER, name + " :No such server"));

	// cmd->queue(ERR_NOSUCHSERVER, "")
}
