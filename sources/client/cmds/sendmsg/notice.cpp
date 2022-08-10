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

static void	nsend_channel(irc::Command* cmd, const std::string& ch_name)
{
	irc::Server*			server = cmd->getServer();
	std::string				msg;
	const std::string&		sender_msg = cmd->getTrailing();
	irc::Client*			client = cmd->getClient();
	irc::Channel*			channel = server->getChannel(ch_name);

	if (!channel)
		return ;

	if (channel->hasMode('n') && !channel->isMember(client))
		return ;

	if (channel->hasMode('m') && !(has_o_O_v(channel, client)))
		return ;

	const irc::Channel::clients_t&	chcls = channel->getClients();
	irc::Channel::clients_t::iterator it = chcls.begin();

	msg = server->getPrefix(client) + " ";
	msg += "NOTICE ";
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

static void	nsend_receiver(irc::Command* cmd, const std::string& nick)
{
	irc::Server*		server = cmd->getServer();
	std::string			msg;
	const std::string&	sender_msg = cmd->getTrailing();
	irc::Client*		cli = server->getClient(nick);

	if (!cli)
		return ;

	msg = server->getPrefix(cmd->getClient()) + " ";
	msg += "NOTICE ";
	msg += cli->getNick();
	msg += " :";
	msg += sender_msg;
	cli->queue(msg);
}

void	irc::cmd::notice	(irc::Command* cmd)
{
	std::string					msg;

	if (cmd->getArgC() < 1)
		return ;
	else if (cmd->getTrailing().empty())
		return ;

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
			nsend_channel(cmd, nicks[i]);
		else
			nsend_receiver(cmd, nicks[i]);
	}
}
