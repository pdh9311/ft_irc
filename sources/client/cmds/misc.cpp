#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"

#include <ctime>

namespace irc
{
	namespace cmd
	{
		void	kill	(Command* cmd)
		{

		}

		void	ping	(Command* cmd)
		{
			// client should not call ping command. Ignore? nvm, irssi sends ping
			if (cmd->getArgC() < 1)
				return ; // ping won't send ERR_NEEDMOREPARAMS
			const std::string&	targ = cmd->getArgs()[0];
			if (cmd->getClient()->getNick() == targ)
				cmd->getServer()->queue(cmd->getClient()->getFD(),
					cmd->getServer()->getPrefix(cmd->getClient()) + "PONG " + targ);
		}

		void	pong	(Command* cmd)
		{
			const std::string& a1 = cmd->getArgs()[0];
			if (a1.empty())
				return (cmd->setResult(ERR_NOORIGIN));
			cmd->getClient()->setLastPing(std::time(0)); // does pong arg have to match nick?
		}

		void	error	(Command* cmd)
		{

		}
	}
}
