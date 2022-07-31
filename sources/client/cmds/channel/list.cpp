#include "channel.hpp"

void	irc::cmd::list(Command *cmd)
{
	// std::cout << "LIST CALLED" << cmd->getArgC() << std::endl;
	// std::cout << cmd->getArgs()[0] << "#" << std::endl;
	if (cmd->getArgC() > 1)
		cmd->setResult(ERR_NOSUCHSERVER); // we dun know any servers.

	if (!cmd->getArgC()) // list all channels
	{
		const Server::channels_t&	channels = cmd->getServer()->getChannels();
		Server::channels_t::const_iterator	it = channels.begin();

		while (it != channels.end())
		{
			Channel*	channel = it->second;
			std::string	str = cmd->getServer()->getPrefix(cmd->getClient()) + to_string(RPL_LIST);
			str += (" " + cmd->getClient()->getNick() + " ");
			str += ("#" + channel->getName() + ":" + channel->getTopic());
			cmd->getServer()->queue(cmd->getClient(), str);
			++it;
		}
		cmd->setResult(RPL_LISTEND);
	}
	else
	{

	}
}