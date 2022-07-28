// #include "client/Client.hpp"
// #include "client/Command.hpp"
// #include "server/Server.hpp"
#include <iostream>

namespace irc
{
	class Command;

	namespace cmd
	{
		/*	connection.cpp	*/
		void	pass	(Command* cmd);
		void	nick	(Command* cmd);
		void	user	(Command* cmd);
		void	server	(Command* cmd);
		void	oper	(Command* cmd);
		void	quit	(Command* cmd);
		void	squit	(Command* cmd);

		/*	channel.cpp	*/
		void	join	(Command* cmd);
		void	part	(Command* cmd);
		void	mode	(Command* cmd);
		void	topic	(Command* cmd);
		void	names	(Command* cmd);
		void	list	(Command* cmd);
		void	invite	(Command* cmd);
		void	kick	(Command* cmd);

		/*	server.cpp	*/
		void	motd	(Command* cmd);
		void	lusers	(Command* cmd);
		void	version	(Command* cmd);
		void	stats	(Command* cmd);
		void	links	(Command* cmd);
		void	time	(Command* cmd);
		void	connect	(Command* cmd);
		void	trace	(Command* cmd);
		void	admin	(Command* cmd);
		void	info	(Command* cmd);

		/*	smesg.cpp	*/
		void	privmsg	(Command* cmd);
		void	notice	(Command* cmd);

		/*	queries.cpp	*/
		void	who		(Command* cmd);
		void	whois	(Command* cmd);
		void	whowas	(Command* cmd);

		/*	misc.cpp	*/
		void	kill	(Command* cmd);
		void	ping	(Command* cmd);
		void	pong	(Command* cmd);
		void	error	(Command* cmd);

		/*	optional.cpp	*/
		void	away	(Command* cmd);
		void	rehash	(Command* cmd);
		void	restart	(Command* cmd);
		void	summon	(Command* cmd);
		void	users	(Command* cmd);
		void	wallops	(Command* cmd);
		void	userhost(Command* cmd);
		void	ison	(Command* cmd);

	}
}
