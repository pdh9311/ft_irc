#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

/*
	Command: USER
	Parameters: <username> <hostname> <servername> <realname>
	Example:
		USER guest tolmoon tolsun :Ronnie Reagan
			; "guest"라는 사용자 이름과 실명 "Ronnie Reagan"으로 자신을 등록하는 사용자.
	Numeric Replies:
		ERR_NEEDMOREPARAMS
		ERR_ALREADYREGISTRED
*/
void	irc::cmd::user(irc::Command* cmd)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;

	if (cmd->getArgC() < 3) // 1 is trailing
	{
		cmd->queue(ERR_NEEDMOREPARAMS);
		return ;
	}

	const std::string&	username = cmd->getArgs()[0];
	const std::string&	hostname = cmd->getArgs()[2];
	const std::string&	realname = cmd->getTrailing();

	if (cmd->getClient()->isLoggedIn())
	{
		msg = ":" + cmd->getClient()->getNick() + "!" + username + "@" + cmd->getServer()->getName() + " ";
		msg += to_string(ERR_ALREADYREGISTRED) + " ";
		msg += username + " :Unauthorized command (already registered)";
		cmd->queue(msg);
		return ;
	}

	irc::Client*	client = cmd->getClient();
	client->setUserName(username);
	client->setHostName(hostname);
	client->setRealName(realname);
	client->setStatus(irc::Client::LOGGEDIN);
	if (!client->getNick().empty())
	{
		client->setWelcome(true);
		msg = ":Welcome to the Internet Relay Network ";
		msg += client->getNick() + "!" + client->getUserName() + "@" + server->getName();
		cmd->queue(RPL_WELCOME, msg);

		motd(cmd);
	}
}
