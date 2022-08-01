#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "../../channel/Channel.hpp"
#include "util.hpp"

namespace irc
{
	namespace cmd
	{
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
		void	privmsg	(Command* cmd)
		{
			Server*							server = cmd->getServer();
			std::string						msg;

			std::string						nickarg = cmd->getArgs()[0];
			std::vector<std::string>		nicks = split(nickarg);

			Server::clients_t				clients = server->getClients();
			Server::clients_t::iterator		cliter;

			Server::channels_t				channels = server->getChannels();
			Server::channels_t::iterator	chiter;
			Channel::clients_t				chcl;
			Channel::clients_t::iterator	chcliter;

			std::string						sender_msg = cmd->getArgs()[1].substr(1);
			Client*							receiver = NULL;
			// 보낼 메시지가 있는지 확인
			if (sender_msg.size() == 0)
			{
				msg = ":No text to send";
				cmd->queue(ERR_NOTEXTTOSEND, msg);
				return ;
			}

			// 수신자가 중복되는 수신자인지 판단.
			for (int i = 0; i < nicks.size() - 1; i++)
			{
				for (int j = i + 1; j < nicks.size(); j++)
				{
					if (nicks[i] == nicks[j])
					{
						msg = nicks[i] + " :Duplicate recipients. No message delivered";
						cmd->queue(ERR_TOOMANYTARGETS, msg);
						return ;
					}
				}
			}

			// 수신자가 채널인지 아닌지 판단.
			// 수신자가 현재 서버에 존재하는지 확인
			for (int i = 0; i < nicks.size(); i++)
			{
				// 수신자가 채널인 경우 - 채널이 있는지 확인하고, 채널에 있는 사람들에게 보낸다.
				if (nicks[i][0] == '#')
				{
					nicks[i] = nicks[i].substr(1);
					for (chiter = channels.begin(); chiter != channels.end(); ++chiter)
					{
						if (nicks[i] == (*chiter).first)	// 채널을 찾음
						{
							chcl = ((*chiter).second)->getClients();	// 채널에 있는 수신자들
							for (chcliter = chcl.begin(); chcliter != chcl.end(); ++chcliter)
							{
								int chcl_fd = *chcliter;
								msg = server->getPrefix(server->getClients().at(chcl_fd)) + " ";
								// msg += to_string(rcode) + " ";
								msg += sender_msg;
								server->queue(chcl_fd, msg);
							}
							break ;
						}
					}
					if (chiter == channels.end())
					{
						msg = "#" + nicks[i] + " :No such nick/channel";
						cmd->queue(ERR_NOSUCHNICK, msg);

						msg = "#" + nicks[i] + " :Cannot send to channel";
						cmd->queue(ERR_CANNOTSENDTOCHAN, msg);
						return ;
					}
					continue ;
				}
				// 수신자가 채널이 아닌 경우 - 서버에 수신자가 있는지 확인
				for (cliter = clients.begin(); cliter != clients.end(); ++cliter)
				{
					receiver = (*cliter).second;
					if (nicks[i] == receiver->getNick())
					{
						int	receiver_fd = receiver->getFD();
						msg = server->getPrefix(receiver) + " ";
						// msg += to_string(rcode) + " ";
						msg += sender_msg;
						server->queue(receiver_fd, msg);
						continue ;
					}
				}
				if (cliter == clients.end())
				{
					msg = nicks[i] + " :No such nick/channel";
					cmd->queue(ERR_NOSUCHNICK, msg);
					msg = ":No recipient given privmsg";	// 수신자의 이름이 잘못되었다.
					cmd->queue(ERR_NORECIPIENT, msg);
					return ;
				}
			}
		}

		void	notice	(Command* cmd)
		{
			privmsg(cmd);
		}
	}
}
