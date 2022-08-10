#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "channel/Channel.hpp"
#include "util.hpp"

void	irc::cmd::kill	(irc::Command* cmd)
{
	if (cmd->getArgC() < 1 || cmd->getTrailing().empty())
		return (cmd->queue(ERR_NEEDMOREPARAMS));
	
	const std::string&	name = cmd->getArgs()[0];
	Server*	serv = cmd->getServer();
	Client*	cli = cmd->getClient();
	Client*	targ = serv->getClient(name);

	if (!(cli->hasMode('o') || cli->hasMode('O')))
		return (cmd->queue(ERR_NOPRIVILEGES));
	if (!targ)
		return (cmd->queue(ERR_NOSUCHNICK, name + " :No such nick/channel"));

	Server::channels_t	chans = serv->getChannels();
	Server::channels_t::const_iterator	it = chans.begin();

	while (it != chans.end())
	{
		Channel*	chan = it->second;
		if (chan->isMember(targ))
		{
			const Channel::clients_t&	clients = chan->getClients();
			Channel::clients_t::const_iterator	cit;
			for (cit = clients.begin(); cit != clients.end(); ++cit)
			{
				Client*	client = serv->getClient(*cit);
				if (targ->getNick() != client->getNick())
					client->queue(serv->getPrefix(targ) + " QUIT :Killed by " + cli->getNick() + " reason: " + cmd->getTrailing());
			}
			chan->rmClient(targ);
		}
		++it;
	}
	targ->queue(serv->getPrefix(targ) + " KILL :" + cmd->getTrailing());
	serv->rmClient(targ);
}
