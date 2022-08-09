#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

/*
	Command: NICK
	Parameters: <nickname> [ <hopcount> ]
	Example:
		NICK Wiz
			; 새로운 닉네임 "위즈"를 소개합니다.
		:WiZ NICK Kilroy
			; WiZ는 닉네임을 킬로이로 변경했습니다.
	Numeric Replies:
		ERR_NONICKNAMEGIVEN
		ERR_ERRONEUSNICKNAME
		ERR_NICKNAMEINUSE
		ERR_NICKCOLLISION
*/
void	irc::cmd::nick(irc::Command* cmd)
{
	irc::Server*		server = cmd->getServer();
	std::string			msg;

	if (cmd->getArgC() < 1)
	{
		msg = ":No nickname given";
		cmd->queue(ERR_NONICKNAMEGIVEN, msg);	// no arg
		return ;
	}
	
	const std::string&	nick = cmd->getArgs()[0];

	if (!nick.size())
	{
		msg = ":No nickname given";
		cmd->queue(ERR_NONICKNAMEGIVEN, msg);	// no nick
		return ;
	}

	if (nick.size() > 9 || !isNickStr(nick))
	{
		msg = ":Erroneus nickname";
		cmd->queue(ERR_ERRONEUSNICKNAME, msg);
		return ;
	}

	Client* find_client = server->getClient(nick);
	if (find_client != NULL)
	{
		msg = ": ";
		msg += to_string(ERR_NICKNAMEINUSE) + " * ";
		msg += nick + " :Nickname is already in use";
		cmd->queue(msg);
		return ;
	}

	// ERR_NICKCOLLISION? check if it's S2S

	Client* client = cmd->getClient();
	client->setNick(nick);
	if (client->getPastName().empty())
		client->setPastName(nick);
	msg = ":";
	if (client->getWelcome() == true)
	{
		msg += client->getPastName(); + "!" + client->getUserName() + "@" + server->getName();
		client->setPastName(client->getNick());
	}
	msg += " NICK :" + cmd->getArgs()[0];
	cmd->queue(msg);
	if (client->getStatus() == Client::LOGGEDIN && client->getWelcome() == 0)
	{
		msg = ":Welcome to the Internet Relay Network ";
		msg += client->getNick() + "!" + client->getUserName() + "@" + cmd->getServer()->getName();
		cmd->queue(RPL_WELCOME, msg);

		motd(cmd);
		client->setWelcome(1);
	}
}
