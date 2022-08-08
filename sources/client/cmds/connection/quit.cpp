#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "channel/Channel.hpp"
#include "util.hpp"

void	irc::cmd::quit(irc::Command* cmd)
{
	Server*	serv = cmd->getServer();
	Client*	cli = cmd->getClient();
	const Server::channels_t	chans = serv->getChannels();
	Server::channels_t::const_iterator	it = chans.begin();

	while (it != chans.end())
	{
		Channel*	chan = it->second;
		if (chan->isMember(cli))
			chan->broadcast(cli, "QUIT :" + cmd->getTrailing());
		++it;
	}
	serv->rmClient(cli);
}
