#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"

void	irc::cmd::oper(irc::Command* cmd)
{
	if (cmd->getArgC() < 2)
		cmd->queue(ERR_NEEDMOREPARAMS);

	irc::Server*		serv = cmd->getServer();
	irc::Client*		cli = cmd->getClient();
	const std::string&	oper_nick = serv->conf.get_O().getNickname();
	const std::string&	oper_pwd = serv->conf.get_O().getPassword();

	if (oper_nick.empty() || oper_pwd.empty())
		cmd->queue(ERR_NOOPERHOST, ":No O-lines for your host");

	const std::string&	nick = cmd->getArgs()[0];
	const std::string&	pwd = cmd->getArgs()[1];

	if (nick != oper_nick)
		return ;
	if (pwd != oper_pwd)
		return (cmd->queue(ERR_PASSWDMISMATCH, ":Password Incorrect"));
	cmd->queue(RPL_YOUREOPER, ":You are now an IRC operator");
	cli->setMode('o');
	cmd->queue(RPL_UMODEIS, "+" + cli->getModestr());
}
