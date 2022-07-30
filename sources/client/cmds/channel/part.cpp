#include "channel.hpp"

void	irc::cmd::part(Command* cmd)
{
	if (!cmd->getArgC())
		return (cmd->queue(ERR_NEEDMOREPARAMS));

	const std::vector<std::string>	chans = irc::split(cmd->getArgs()[0]);
	Server*	serv = cmd->getServer();
	Client*	cli = cmd->getClient();

	for (size_t i = 0; i < chans.size(); ++i)
	{
		const std::string&	name = chans[i];
		if (name[0] == '#')
		{
			if (!serv->hasChannel(name))
				return (cmd->queue(ERR_NOSUCHCHANNEL, name + " :No such channel"));
			Channel*	chan = serv->getChannel(name);

			if (!chan->isMember(cli))
				return (cmd->queue(ERR_NOTONCHANNEL, chan->getName() + " :You're not on that channel"));
			chan->rmClient(cli);
		}
	}
}