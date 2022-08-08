#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

void	irc::cmd::kill	(irc::Command* cmd)
{
	std::string	msg;
	std::string	user_str = cmd->getArgs()[0];

	if (cmd->getArgC() < 1 || cmd->getTrailing().empty() == true)
		return (cmd->queue(ERR_NEEDMOREPARAMS));
	const irc::Server::clients_t&			clients = cmd->getServer()->getClients();
	irc::Server::clients_t::const_iterator	it = clients.begin();
	irc::Client* client;
	while (it != clients.end())
	{
		if (it->second->getNick() == user_str)
			break;
		++it;
	}
	if (it == clients.end())
			return (cmd->queue(ERR_NOSUCHNICK, user_str + " :No such nick/channel"));
	client = it->second;
	if (cmd->getClient()->hasMode('o') == 0 && cmd->getClient()->hasMode('O') == 0)
		return (cmd->queue(ERR_NOPRIVILEGES));
	cmd->getServer()->rmClient(client); //실패시 ERR_CANTKILLSERVER
	msg = cmd->getServer()->getPrefix(cmd->getClient()) + " KILL :" + cmd->getTrailing().substr(1);
	client->queue(msg);
	msg = cmd->getServer()->getPrefix(cmd->getClient()) + " QUIT :" + cmd->getTrailing().substr(1);
	client->queue(msg);
}
