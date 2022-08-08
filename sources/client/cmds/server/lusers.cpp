#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "client/Client.hpp"
#include "channel/Channel.hpp"
#include "util.hpp"

/*
	Command: LUSERS
	Parameters: [ <mask> [ <target> ] ]
	Numeric Replies:
		RPL_LUSERCLIENT
		RPL_LUSEROP
		RPL_LUSERUNKOWN
		RPL_LUSERCHANNELS
		RPL_LUSERME
		ERR_NOSUCHSERVER
*/
void	irc::cmd::lusers	(irc::Command* cmd)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;

	if (cmd->getArgC() != 0)
	{
		msg = cmd->getArgs()[0];
		msg += " :No such server";
		cmd->queue(ERR_NOSUCHSERVER, msg);
		return ;
	}
	msg = ": Three are ";
	msg+= irc::itos(server->getClients().size());	
	msg += " and <integer> services on 1 servers";
	cmd->queue(RPL_LUSERCLIENT, msg);

	int	operatorCnt = 0;
	irc::Server::clients_t	clients = server->getClients();
	irc::Server::clients_t::iterator clit;
	for (clit = clients.begin(); clit != clients.end(); ++clit)
	{
		irc::Client* client = clit->second;
		if (client->hasMode('o') || client->hasMode('O'))
			operatorCnt++;
	}
	msg = irc::itos(operatorCnt) + " :operator(s) online";
	cmd->queue(RPL_LUSEROP, msg);

	msg = "<integer> :unknown connection(s)";	
	cmd->queue(RPL_LUSERUNKNOWN, msg);

	msg = server->getChannels().size();
	msg += " :channels formed";
	cmd->queue(RPL_LUSERCHANNELS, msg);

	msg = ":I have ";
	msg += irc::itos(server->getClients().size());
	msg += " clients and 1 servers";
	cmd->queue(RPL_LUSERME, msg);
}
