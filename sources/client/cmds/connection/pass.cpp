#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

/*
	Command: PASS
	Parameters: <password>
	Example:
		PASS <password>
	Numeric Replies:
		ERR_NEEDMOREPARAMS
		ERR_ALREADYREGISTRED
*/
void	irc::cmd::pass(irc::Command* cmd)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;

	if (cmd->getArgC() < 1)
	{
		cmd->queue(ERR_NEEDMOREPARAMS);
		return ;
	}
	if (cmd->getClient()->isLoggedIn())
	{
		msg = ":Unauthorized command (already registered)";
		cmd->queue(ERR_ALREADYREGISTRED, msg);
		return ;
	}
	const std::string&	pwd = cmd->getArgs()[0];
	if (pwd == server->getPass())
		cmd->getClient()->setStatus(Client::AUTH);
	else // is this needed?
		cmd->getClient()->setStatus(Client::PENDING);
}
