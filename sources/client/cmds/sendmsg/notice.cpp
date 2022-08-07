#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "channel/Channel.hpp"
#include "util.hpp"

static void	nsend_channel(irc::Command* cmd, std::vector<std::string>& ch_name, size_t i)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;
	std::string		sender_msg = cmd->getArgs()[1].substr(1);
	irc::Client*	client = cmd->getClient();
	irc::Channel*	channel = server->getChannel(ch_name[i]);

	if (channel == NULL)
	{
		cmd->queue(ERR_NOSUCHNICK, ch_name[i] + " :No such nick/channel");
		return ;
	}
	const irc::Channel::clients_t&	chcls = channel->getClients();
	irc::Channel::clients_t::iterator it = chcls.begin();

	msg = server->getPrefix(client) + " ";
	msg += "NOTICE ";
	msg += channel->getFName();
	msg += " :";
	msg += sender_msg;

	while (it != chcls.end())
	{
		irc::Client* cli = server->getClient(*it);
		if (cli && cli->getNick() != client->getNick())
			cli->queue(msg);
		++it;
	}
}

static void	nsend_receiver(irc::Command* cmd, std::vector<std::string>& nicks, size_t i)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;
	std::string		sender_msg = cmd->getArgs()[1].substr(1);
	irc::Client*	cli = server->getClient(nicks[i]);

	if (cli == NULL)
	{
		msg = nicks[i] + " :No such nick/channel";
		cmd->queue(ERR_NOSUCHNICK, msg);
		return ;
	}

	msg = server->getPrefix(cmd->getClient()) + " ";
	msg += "NOTICE ";
	msg += cli->getNick();
	msg += " :";
	msg += sender_msg;
	server->queue(cli->getFD(), msg);
}

void	irc::cmd::notice	(irc::Command* cmd)
{
	std::string					msg;
	std::vector<std::string>	nicks = irc::split(cmd->getArgs()[0]);
	std::string					sender_msg = cmd->getArgs()[1].substr(1);

	// 수신자가 채널인지 아닌지 판단. // 수신자가 현재 서버에 존재하는지 확인
	for (size_t i = 0; i < nicks.size(); i++)
	{
		// 수신자가 채널인 경우 - 채널이 있는지 확인하고, 채널에 있는 사람들에게 보낸다.
		if (irc::isChPrefix(nicks[i][0]))
		{
			nsend_channel(cmd, nicks, i);
			continue ;
		}
		nsend_receiver(cmd, nicks, i);
	}
}
