#include "channel.hpp"

void	irc::cmd::topic(Command* cmd)
{
	if (!cmd->getArgC())
		cmd->setResult(ERR_NEEDMOREPARAMS);
	const std::string&	name = cmd->getArgs()[0];
	if (!cmd->getServer()->hasChannel(name))
		return (cmd->setResult(ERR_NOSUCHCHANNEL));

	Channel*		channel = cmd->getServer()->getChannel(name);
	if (channel->getTopic().empty())
		return (cmd->setResult(RPL_NOTOPIC));
	return (cmd->setResult(RPL_TOPIC, channel->getTopic()));	
}