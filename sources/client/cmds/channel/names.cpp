#include "channel.hpp"

void	irc::cmd::names(Command* cmd)
{
	Client*				cli = cmd->getClient();
	Server*				serv = cmd->getServer();

	if (!cmd->getArgC())
	{
		Server::channels_t	chans = serv->getChannels();
		Server::channels_t::const_iterator	it = chans.begin();
		while (it != chans.end())
		{
			it->second->sendNames(cli);
			++it;
		}
		// need to implement 
		return ;
	}

	std::vector<std::string>	chans = split(cmd->getArgs()[0]);
	std::vector<std::string>::const_iterator	it = chans.begin();
	while (it != chans.end())
	{
		Channel*	chan = serv->getChannel(*it);
		if (!chan)
			continue ; //no error reply per rfc
		chan->sendNames(cli);
		++it;
	}
}