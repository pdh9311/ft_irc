#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "channel/Channel.hpp"
#include "client/numerics.hpp"
#include "util.hpp"
#include <ctime>

	// ERR_NOSUCHSERVER
	// ERR_NONICKNAMEGIVEN
	// RPL_WHOISUSER
	// RPL_WHOISCHANNELS
	// RPL_WHOISCHANNELS
	// RPL_WHOISSERVER
	// RPL_AWAY
	// RPL_WHOISOPERATOR
	// RPL_WHOISIDLE
	// ERR_NOSUCHNICK
	// RPL_ENDOFWHOIS

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
		msg = cmd->getArgs()[0] + " " + client->getUserName() + " " + client->getHostName() + " * " + client->getRealName();
		cmd->queue(RPL_WHOISUSER, msg);
		
        if (client->hasMode('o'))
		{
			msg = client->getNick();
			cmd->queue(RPL_WHOISOPERATOR, msg);
		}
		if (client->isOnChannel())
		{
			Server::channels_t	chans = serv->getChannels();
			Server::channels_t::const_iterator	it = chans.begin();
			while (it != chans.end())
			{
				if (it->second->isMember(client))
				{
					msg = client->getNick() + " ";
					if (it->second->hasUserMode(client, 'o') || it->second->hasUserMode(client, 'O') || client->hasMode('o'))
						msg += '@';
					if (it->second->hasUserMode(client, 'v'))
						msg += '+';
					cmd->queue(RPL_WHOISCHANNELS, msg + it->second->getFName());					
				}
				it++;
			}
		}   
		msg = client->getNick();
		cmd->queue(RPL_ENDOFWHOIS, msg);
		return ;
	}
	return (cmd->queue(ERR_NOSUCHNICK, user_str + " :No such nick/channel"));
}
