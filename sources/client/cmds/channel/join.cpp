#include "channel.hpp"

void	irc::cmd::join(Command *cmd)
{
	if (!cmd->getArgC())
		return (cmd->setResult(ERR_NEEDMOREPARAMS));

	const std::vector<std::string>	channs = irc::split(cmd->getArgs()[0]);
	const std::vector<std::string>	keys = (cmd->getArgC() > 1 ? irc::split(cmd->getArgs()[1]) : std::vector<std::string>());
	Client*	cli = cmd->getClient();
	Server*	serv = cmd->getServer();

	// if (cmd->getArgs()[0] == "0")
	// {
	// 	const Server::channels_t	channels = serv->getChannels();
	// 	Server::channels_t::const_iterator	it = channels.begin();
	// 	while (it != channels.end())
	// 	{
	// 		Channel*	chan = it->second;

	// 		if (chan->isMember(cli))
	// 			chan->rmClient(cli);
	// 	}
	// 	return ;
	// }

	Channel*	tmp = 0;

	for (size_t i = 0; i < channs.size(); ++i)
	{
		const std::string&	name = channs[i];
		
		// std::cout << "sanity check:" << name << std::endl;
		// if (name[0] != '#')
		// 	return (cmd->queue(ERR_NOSUCHCHANNEL, name + " :No such server"));
		Channel*	chan = serv->getChannel(name);
		if (!chan)
			chan = serv->addChannel(name);
		if (chan->hasMode('k'))
		{
			const std::string	key = (keys.size() > i ? keys[i] : "");
			if (key != chan->getKey())
			{
				cmd->queue(ERR_BADCHANNELKEY, chan->getName() + " :Cannot join channel (+k)");
				continue ;
			}
		}
		if (chan->hasMode('l') && (chan->getSize() == chan->getMaxClient()))
		{
			cmd->queue(ERR_CHANNELISFULL, chan->getName() + " :Cannot join channel (+l)");
			continue;
		}
		if (chan->hasMode('i') && !chan->isInvited(cli)) //operator check?
		{
			cmd->queue(ERR_INVITEONLYCHAN, chan->getName() + " :Cannot join channel (+i)");
			continue ;
		}

		chan->addClient(cli);
		if (chan->getSize() == 1)
			chan->setUserMode(cli, 'o');
		// cli->setCChannel(chan);
		tmp = chan;
		cli->setOnChannel(true);
		chan->sendNames(cli);
		chan->broadcast(cli, "JOIN :" + chan->getFName());
	}

	// const Channel*	chan = cli->getCChannel();
	if (tmp && !tmp->getTopic().empty())
		cmd->queue(RPL_TOPIC, tmp->getFName() + " :" + tmp->getTopic());
}
