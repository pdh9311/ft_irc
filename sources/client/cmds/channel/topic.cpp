#include "channel.hpp"

void	irc::cmd::topic(Command* cmd)
{
	if (!cmd->getArgC())
		return (cmd->queue(ERR_NEEDMOREPARAMS));
	const std::string&	name = cmd->getArgs()[0];
	const std::string	topic = cmd->getTrailing();
	Server*				serv = cmd->getServer();
	Client*				cli = cmd->getClient();
	Channel*			chan = serv->getChannel(name);

	if (!chan)
		return (cmd->queue(ERR_NOSUCHCHANNEL, name + " :No such channel"));
	if (!chan->isMember(cli))
		return (cmd->queue(ERR_NOTONCHANNEL, chan->getFName() + " :You're not on that channel"));

	if (topic.empty())
	{
		if (chan->getTopic().empty())
			return (cmd->queue(RPL_NOTOPIC, chan->getFName() + " :No topic is set"));
		return (cmd->queue(RPL_TOPIC, chan->getTopic()));
	}
	else
	{
		if (chan->hasMode('t') && !(chan->hasUserMode(cli, 'o') || chan->hasUserMode(cli, 'O' || cli->hasMode('o'))))
		 	return (cmd->queue(ERR_CHANOPRIVSNEEDED, chan->getFName() + " :You're not channel operator"));
		chan->setTopic(topic);
		chan->broadcast(cli, "TOPIC " + chan->getFName() + " :" + chan->getTopic());	
	}
}
