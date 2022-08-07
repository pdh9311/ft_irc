#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "channel/Channel.hpp"
#include "util.hpp"

static void	nsend_channel(irc::Command* cmd, std::vector<std::string>& nicks, size_t i)
{
	irc::Server*							server = cmd->getServer();
	std::string						msg;
	irc::Server::channels_t				channels = server->getChannels();
	irc::Server::channels_t::iterator	chiter;
	irc::Channel::clients_t				chcl;
	irc::Channel::clients_t::iterator	chcliter;
	std::string						sender_msg = cmd->getArgs()[1].substr(1);

	nicks[i] = nicks[i].substr(1);
	for (chiter = channels.begin(); chiter != channels.end(); ++chiter)
	{
		if (nicks[i] == (*chiter).first)	// 채널을 찾음
		{
			chcl = ((*chiter).second)->getClients();	// 채널에 있는 수신자들
			for (chcliter = chcl.begin(); chcliter != chcl.end(); ++chcliter)
			{
				// 이름 같은거 말고
				int chcl_fd = *chcliter;
				if (cmd->getClient()->getNick() != server->getClients().at(chcl_fd)->getNick())
				{
					msg = server->getPrefix(cmd->getClient()) + " ";
					msg += "PRIVMSG ";
					msg += chiter->second->getFName();
					msg += " :";
					msg += sender_msg;
					server->queue(chcl_fd, msg);
				}
			}
			break ;
		}
	}
}

static void	nsend_receiver(irc::Command* cmd, std::vector<std::string>& nicks, size_t i)
{
	irc::Server*						server = cmd->getServer();
	std::string							msg;
	irc::Server::clients_t				clients = server->getClients();
	irc::Server::clients_t::iterator	cliter;
	std::string							sender_msg = cmd->getArgs()[1].substr(1);
	irc::Client*						receiver = NULL;

	for (cliter = clients.begin(); cliter != clients.end(); ++cliter)
	{
		receiver = (*cliter).second;
		if (nicks[i] == receiver->getNick())
		{
			int	receiver_fd = receiver->getFD();
			msg = server->getPrefix(cmd->getClient()) + " ";
			msg += "PRIVMSG ";
			msg += receiver->getNick();
			msg += " :";
			msg += sender_msg;
			server->queue(receiver_fd, msg);
			break ;
		}
	}
}

void	irc::cmd::notice	(irc::Command* cmd)
{
	std::string						msg;
	std::vector<std::string>		nicks = irc::split(cmd->getArgs()[0]);
	std::string						sender_msg = cmd->getArgs()[1].substr(1);

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
