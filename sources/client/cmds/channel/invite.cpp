#include "channel.hpp"

void	irc::cmd::invite(Command* cmd)
{
	if (cmd->getArgC() < 2)
		return (cmd->queue(ERR_NEEDMOREPARAMS));

	Server*	serv = cmd->getServer();
	Client*	cli = cmd->getClient();
	
	const std::string&	target = cmd->getArgs()[0];
	const std::string&	chname = cmd->getArgs()[1];

	Client*	tcli = serv->getClient(target);
	if (!tcli)
		return (cmd->queue(ERR_NOSUCHNICK, target + " :No such nick/channel"));
	Channel*	chan = serv->getChannel(chname);
	if (!chan)
		return (cmd->queue(ERR_NOSUCHCHANNEL, chname + " :No such channel"));
	if (!chan->isMember(cli))
		return (cmd->queue(ERR_NOTONCHANNEL, chan->getFName() + " :You're not on that channel"));
	if (chan->isMember(tcli))
		return (cmd->queue(ERR_USERONCHANNEL, chan->getFName() + " :is already on channel"));
	if (chan->hasMode('i') && !(chan->hasUserMode(cli, 'o') || chan->hasUserMode(cli, 'O') || cli->hasMode('o')))
		return (cmd->queue(ERR_CHANOPRIVSNEEDED, chan->getFName() + " :You're not channel operator"));
	tcli->queue(serv->getPrefix(cli) + " INVITE " + target + " " + chname);
	cmd->queue(RPL_INVITING, chname + " " + target);
	chan->inviteMember(tcli);
	if (tcli->hasMode('a'))
		cmd->queue(RPL_AWAY, tcli->getNick() + " :" + tcli->getAwayMsg());	
}
