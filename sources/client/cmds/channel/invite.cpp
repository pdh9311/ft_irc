#include "channel.hpp"

void	irc::cmd::invite(Command* cmd)
{
	if (cmd->getArgC() < 2)
		return (cmd->setResult(ERR_NEEDMOREPARAMS));

	const std::string&	target = cmd->getArgs()[0];
	const std::string&	chann = cmd->getArgs()[1];

	Client*	client = cmd->getServer()->getClient(target);
	if (!client)
		return (cmd->setResult(ERR_NOSUCHNICK));
	if (!cmd->getServer()->hasChannel(chann))
		return (cmd->setResult(ERR_NOSUCHCHANNEL));
	Channel*	channel = cmd->getServer()->getChannel(chann);
	channel->inviteMember(client);
	cmd->setResult(RPL_INVITING, "#" + channel->getName() + " " + client->getNick());
}