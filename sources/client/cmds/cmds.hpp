#include "client/Client.hpp"
#include "client/Command.hpp"
#include "server/Server.hpp"

namespace irc
{
	namespace cmd
	{
		void	nick(Command* cmd);
		void	user(Command* cmd);
		void	server(Command* cmd);
		void	oper(Command* cmd);
		void	quit(Command* cmd);
		void	squit(Command* cmd);
	}
}
