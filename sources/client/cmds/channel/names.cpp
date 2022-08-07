#include "channel.hpp"

void	irc::cmd::names(Command* cmd)
{
	Client*				cli = cmd->getClient();
	Server*				serv = cmd->getServer();

	if (cmd->getArgC() == 2)
		return (cmd->queue(ERR_NOSUCHSERVER, cmd->getArgs()[1] + " :No such server"));

	if (!cmd->getArgC())
	{
		Server::channels_t	chans = serv->getChannels();
		Server::channels_t::const_iterator	it = chans.begin();
		while (it != chans.end())
		{
			Channel*	chan = it->second;
			if ((chan->hasMode('s' || chan->hasMode('p')) && !chan->isMember(cli)))
			{
				++it;
				continue ;
			}
			chan->sendNames(cli);
			++it;
		}
		Server::clients_t	clients = serv->getClients();
		Server::clients_t::const_iterator	cit = clients.begin();
		Client*	client = 0;
		while (cit != clients.end())
		{
			client = cit->second;
			if (!client->isOnChannel())
				cmd->queue(RPL_NAMREPLY, "* :" + client->getNick());
			++cit;
		}
		if (client)
			cmd->queue(RPL_ENDOFNAMES, "* :End of /NAMES list");

		return ;
	}

	std::vector<std::string>	chans = split(cmd->getArgs()[0]);
	std::vector<std::string>::const_iterator	it = chans.begin();
	while (it != chans.end())
	{
		Channel*	chan = serv->getChannel(*it);
		if (chan) // no err msg for unknown channel per rfc
		{
			if ((chan->hasMode('s') || chan->hasMode('p')) && !chan->isMember(cli))
			{
				++it;
				continue ;
			}
			chan->sendNames(cli);
		}
		++it;
	}
}
