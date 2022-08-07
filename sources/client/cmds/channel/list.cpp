#include "channel.hpp"

void	irc::cmd::list(Command *cmd)
{
	if (cmd->getArgC() > 1)
		return (cmd->queue(ERR_NOSUCHSERVER));

	Server*	serv = cmd->getServer();
	// Client*	cli = cmd->getClient();
	
	if (!cmd->getArgC())
	{
		const Server::channels_t&	chans = serv->getChannels();
		Server::channels_t::const_iterator	it = chans.begin();

		while (it != chans.end())
		{
			Channel*	chan = it->second;
			cmd->queue(RPL_LIST, chan->getFName() + " " + irc::itos(chan->getSize()) + " :" + chan->getTopic());
			++it;
		}
	}
	else
	{
		std::vector<std::string>	chans = irc::split(cmd->getArgs()[0]);
		std::vector<std::string>::const_iterator	it = chans.begin();

		while (it != chans.end())
		{
			Channel*	chan = serv->getChannel(*it);
			if (chan)
				cmd->queue(RPL_LIST, chan->getFName() + " " + irc::itos(chan->getSize()) + " :" + chan->getTopic());
			++it;
		}
	}
	cmd->queue(RPL_LISTEND);
}
