#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "channel/Channel.hpp"
#include "util.hpp"

#include <algorithm>
#include <vector>

static bool has_o_O_v(irc::Channel* channel, irc::Client* client)
{
	return (channel->hasUserMode(client, 'o') || channel->hasUserMode(client, 'O') ||
			channel->hasUserMode(client, 'v') || client->hasMode('o'));
}

static void	send_channel(irc::Command* cmd, const std::string& ch_name)
{
	irc::Server*			server = cmd->getServer();
	std::string				msg;
	const std::string&		sender_msg = cmd->getTrailing();
	irc::Client*			client = cmd->getClient();
	irc::Channel*			channel = server->getChannel(ch_name);

	if (!channel)
		return (cmd->queue(ERR_NOSUCHNICK, ch_name + " :No such nick/channel"));

	// n
	// 송신자의 채널이 있는지 확인, 있으면 송신자의 채널 확인
	// 수신자의 채널과 송신자의 채널이 다르면 404
	if (channel->hasMode('n') && !channel->isMember(client))
		return (cmd->queue(ERR_CANNOTSENDTOCHAN, ch_name + " :Cannot send to channel"));

	// m
	// 채널 모드가 m인지 확인, m 이면 채널내에 있는 수신자들 중 O, o, v 옵션이 있는 사람들만 채팅 가능
	if (channel->hasMode('m') && !(has_o_O_v(channel, client)))
		return (cmd->queue(ERR_CANNOTSENDTOCHAN, ch_name + " :Cannot send to channel"));

	const irc::Channel::clients_t&	chcls = channel->getClients();
	irc::Channel::clients_t::iterator it = chcls.begin();

	msg = server->getPrefix(client) + " ";
	msg += "PRIVMSG ";
	msg += channel->getFName();
	msg += " :";
	msg += sender_msg;

	while (it != chcls.end())
	{
		irc::Client* cli = server->getClient(*it);	// 수신자 cli
		if (cli && cli->getNick() != client->getNick())
			cli->queue(msg);
		++it;
	}
}

static void	send_receiver(irc::Command* cmd, const std::string& nick)
{
	irc::Server*		server = cmd->getServer();
	std::string			msg;
	const std::string&	sender_msg = cmd->getTrailing();
	irc::Client*		cli = server->getClient(nick);

	if (!cli)
		return (cmd->queue(ERR_NOSUCHNICK, nick + " :No such nick/channel"));

	msg = server->getPrefix(cmd->getClient()) + " ";
	msg += "PRIVMSG ";
	msg += cli->getNick();
	msg += " :";
	msg += sender_msg;
	cli->queue(msg);
}

/*
	Command: PRIVMSG
	Parameters: <receiver>{,<receiver>} <text to be sent>
	Example:
		:Angel PRIVMSG Wiz :Hello are you receiving this message ?
			; Angel이 Wiz에게 보내는 메시지.
		PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br
			; 엔젤에게 보내는 메시지.
		PRIVMSG jto@tolsun.oulu.fi :Hello !
			; 사용자 이름이 "jto"인 서버 tolsun.oulu.fi의 클라이언트에 대한 메시지입니다.
		PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
			; 이름이 *.fi와 일치하는 서버의 모든 사람에게 보내는 메시지입니다.
		PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
			; 이름이 *.edu와 일치하는 호스트에서 온 모든 사용자에게 보내는 메시지입니다.
	Numeric Replies:
		ERR_NORECIPIENT
		ERR_NOTEXTTOSEND
		ERR_CANNOTSENDTOCHAN
		ERR_NOTOPLEVEL
		ERR_WILDTOPLEVEL
		ERR_TOOMANYTARGETS
		ERR_NOSUCHNICK
		RPL_AWAY
*/
void	irc::cmd::privmsg	(irc::Command* cmd)
{
	std::string					msg;

	if (cmd->getArgC() < 1)
		return (cmd->queue(ERR_NORECIPIENT, ":No recipient given (" + cmd->getCommand() + ")"));
	else if (cmd->getTrailing().empty())
		return (cmd->queue(ERR_NOTEXTTOSEND));

	std::vector<std::string>	nicks = irc::split(cmd->getArgs()[0]);
	const std::string			sender_msg = cmd->getTrailing();

	// 중복 닉네임 간소화
	std::sort(nicks.begin(), nicks.end());
	std::vector<std::string>::iterator	uit = std::unique(nicks.begin(), nicks.end());
	nicks.erase(uit, nicks.end());

	// 수신자가 채널인지 아닌지 판단. // 수신자가 현재 서버에 존재하는지 확인
	for (size_t i = 0; i < nicks.size(); i++)
	{
		// 수신자가 채널인 경우 - 채널이 있는지 확인하고, 채널에 있는 사람들에게 보낸다.
		if (irc::isChPrefix(nicks[i][0]))
			send_channel(cmd, nicks[i]);
		else
			send_receiver(cmd, nicks[i]);
	}
}
