#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

/*
	Command: ISON
	Parameters: <nickname>{<space><nickname>}
	Example:
		ISON phone trillian WiZ jarlek Avalon Angel Monstah
			; 7개의 닉에 대한 샘플 ISON 요청.
	Numeric Replies:
		RPL_ISON
		ERR_NEEDMOREPARAMS
*/
void	irc::cmd::ison	(irc::Command* cmd)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;

	if (cmd->getArgC() == 0)
	{
		cmd->queue(ERR_NEEDMOREPARAMS);
		return ;
	}
	std::string					onicks = cmd->getArgs()[0].substr(1);
	std::vector<std::string>	nicks = irc::split(onicks, ' ');
	std::vector<std::string>	online;
	std::map<int, Client*>		clients = server->getClients();

	std::map<int, Client*>::iterator	it;
	for (it = clients.begin(); it != clients.end(); ++it)
	{
		std::vector<std::string>::iterator	nit;
		for (nit = nicks.begin(); nit != nicks.end(); ++nit)
		{
			if ((*it).second->getNick() == (*nit))
			{
				online.push_back((*it).second->getNick());
				break ;
			}
		}
	}
	if (online.size() == 0)
		msg = ":[]";
	else
	{
		msg = ":[";
		std::vector<std::string>::iterator oit;
		for (size_t i = 0; i < online.size(); i++)
		{
			msg += online[i];
			if (i != online.size() - 1)
				msg += " ";
		}
		msg += "]";
	}
	cmd->queue(RPL_ISON, msg);	// ":[<nick> {<space><nick>}]"
}
