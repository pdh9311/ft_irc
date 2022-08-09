#include "channel.hpp"


bool	isChannel(irc::Server::channels_t channels, const std::string& channel_name)
{
	irc::Server::channels_t::iterator	it;
	for (it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->first == channel_name)
			return (true);
	}
	return (false);
}

/*
	Command: KICK
	Parameters: <channel> <user> [<comment>]
	Example:
		KICK &Melbourne Matthew
			; &Melbourne의 킥 매튜
		KICK #Finnish John :Speaking English
			; "영어 말하기"를 이유(댓글)로 사용하여 #Finnish에서 John을 걷어차십시오.
		:WiZ KICK #Finnish John
			; 채널 #Finnish에서 John을 제거하라는 WiZ의 KICK 메시지
	Numeric Replies:
		ERR_NEEDMOREPARAMS
		ERR_NOSUCHCHANNEL
		ERR_BADCHANMASK
		ERR_CHANOPRIVSNEEDED
		ERR_NOTONCHANNEL
*/
void	irc::cmd::kick(Command* cmd)
{
	Server*	server = cmd->getServer();
	if (!cmd->getArgC())
		return (cmd->queue(ERR_NEEDMOREPARAMS));
	const std::string	channel_name = cmd->getArgs()[0];	// 채널명
	std::string	msg;

	if (cmd->getArgC() != 2 && cmd->getArgC() != 3)
	{
		cmd->queue(ERR_NEEDMOREPARAMS);
		return ;
	}
	if (isChannel(server->getChannels(), channel_name.substr(1)) == false)
	{
		msg = channel_name + " :No such channel";
		cmd->queue(ERR_NOSUCHCHANNEL, msg);
		return ;
	}
	if (!isChPrefix(channel_name[0]))
	{
		msg = channel_name + " :Bad Channel Mask";
		cmd->queue(ERR_BADCHANMASK, msg);
		return ;
	}
	for (size_t	i = 0; i < channel_name.size() - 1; i++)
	{
		if (isChString((channel_name.substr(1))[i]) == false)
		{
			msg = channel_name + " :Bad Channel Mask";
			cmd->queue(ERR_BADCHANMASK, msg);
			return ;
		}
	}

	irc::Server::channels_t			channels = server->getChannels();
	Channel*						channel = channels[channel_name.substr(1)];

	std::string						kicked_nick = cmd->getArgs()[1];
	Client*							kicked_client = server->getClient(kicked_nick);

	Channel::clients_t				clients = channel->getClients();
	Channel::clients_t::iterator	it = clients.find(kicked_client->getFD());
	if (it == clients.end())
	{
		msg = channel_name + " :You're not on that channel";
		cmd->queue(ERR_NOTONCHANNEL, msg);
		return ;
	}

	Client*	client = cmd->getClient();
	if (!(channel->hasUserMode(client, 'o') ||
		channel->hasUserMode(client, 'O') ||
		cmd->getClient()->hasMode('o')))
	{
		msg = channel_name + " :You're not channel operator";
		cmd->queue(ERR_CHANOPRIVSNEEDED, msg);
		return ;
	}

	msg = "KICK " + channel_name + " " + cmd->getArgs()[1];
	msg += " :";

	channel->broadcast(client, msg);
	channel->rmClient(server->getClient(*it));
}
