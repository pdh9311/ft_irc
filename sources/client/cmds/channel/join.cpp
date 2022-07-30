#include "channel.hpp"

void	irc::cmd::join(Command *cmd)
{
	if (!cmd->getArgC())
		return (cmd->setResult(ERR_NEEDMOREPARAMS));

	const std::vector<std::string>	channs = irc::split(cmd->getArgs()[0]);
	Client*	cli = cmd->getClient();
	Server*	serv = cmd->getServer();

	for (size_t i = 0; i < channs.size(); ++i)
	{
		const std::string&	name = channs[i];
		
		if (name[0] == '#')
		{
			Channel*	chan = serv->getChannel(name);
			if (!chan)
				chan = serv->addChannel(name);
			chan->addClient(cli);
			cli->setCChannel(chan);
		}
	}

	const Channel*	chan = cli->getCChannel();
	if (chan && !chan->getTopic().empty())
		cmd->queue(RPL_TOPIC, chan->getFName() + " :" + chan->getTopic());
}