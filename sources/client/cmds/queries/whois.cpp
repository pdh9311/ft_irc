#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"

void	irc::cmd::whois	(irc::Command* cmd)
{
	std::string msg;
    if (cmd->getArgC() < 1)
    {
        msg = ":No nickname given";
        cmd->queue(ERR_NONICKNAMEGIVEN, msg);   // no arg
        return ;
    }
	
	std::string channels_names;
    Server* serv = cmd->getServer();
    Client *client;
    std::string user_str = cmd->getArgs()[0];
    client = serv->getClient(user_str);
	
	if (client != NULL)
    {
		cmd->queue(RPL_UMODEIS, "+ " + client->getModestr());
		msg = cmd->getArgs()[0] + " " + client->getUserName() + " " + client->getHostName() + " * " + client->getRealName();
		cmd->queue(RPL_WHOISUSER, msg);
		msg = client->getNick() + " " + serv->getName();
       	cmd->queue(RPL_WHOISSERVER, msg);
		if (client->hasMode('o'))
		{
			msg = client->getNick();
			cmd->queue(RPL_WHOISOPERATOR, msg);
		}
		msg = client->getNick();
		cmd->queue(RPL_ENDOFWHOIS, msg);
		return ;
	}
	return (cmd->queue(ERR_NOSUCHNICK, user_str + " :No such nick/channel"));
}
