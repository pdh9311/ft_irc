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
/*
ERR_NEEDMOREPARAMS
	"<command> :Not enough parameters"
ERR_NOSUCHCHANNEL
	"<channel name> :No such channel"
ERR_BADCHANMASK
	"<channel> :Bad Channel Mask"
ERR_CHANOPRIVSNEEDED
	"<channel> :You're not channel operator"
ERR_NOTONCHANNEL
	"<channel> :You're not on that channel"
*/
// argc : 2
// args[0] : 채널명
// args[1] : nickname
void	irc::cmd::kick(Command* cmd)
{
	Server*	server = cmd->getServer();
	std::string	channel_name = cmd->getArgs()[0];	// 채널명
	std::string	msg;

	// std::cout << cmd->getArgC() << " " << cmd->getArgs()[0] << " " << cmd->getArgs()[1] << std::endl;
	// if (!cmd->getArgs()[2].empty())
	// 	std::cout << cmd->getArgs()[2] << std::endl;

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
	Client*							client = server->getClient(kicked_nick);

	Channel::clients_t				clients = channel->getClients();
	Channel::clients_t::iterator	it = clients.find(client->getFD());
	if (it == clients.end())
	{
		msg = channel_name + " :You're not on that channel";
		cmd->queue(ERR_NOTONCHANNEL, msg);
		return ;
	}

	// ERR_CHANOPRIVSNEEDED
	// 	"<channel> :You're not channel operator"
	
	// clients.erase(*it);

	// msg = ":" + client->getNick() + "!" + client->getUserName() + "@" + server->getName();
	// msg += " KICK " + channel_name + " " + cmd->getArgs()[1];
	// msg += " :";
	// server->queue(client->getFD(), msg);

	// msg = ":" + client->getNick() + "!" + client->getUserName() + "@" + server->getName();
	msg = "KICK " + channel_name + " " + cmd->getArgs()[1];
	msg += " :";

	// cmd->queue(msg);
	channel->broadcast(cmd->getClient(), msg);
	channel->rmClient(server->getClient(*it));
}
