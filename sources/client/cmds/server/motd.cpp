#include "client/cmds/cmds.hpp"
#include "client/Command.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

#include <fstream>

/*
	Command: MOTD
	Parameters: [ <target> ]
	Numeric Replies:
		RPL_MOTDSTART
		RPL_MOTD
		RPL_ENDOFMOTD
		ERR_NOMOTD
*/
void	irc::cmd::motd	(irc::Command* cmd)
{
	irc::Server*	server = cmd->getServer();
	std::string		msg;

	msg = ":- " + server->getName() + " Message of the day - ";
	cmd->queue(RPL_MOTDSTART, msg);

	std::ifstream	file("motd.txt");
	char			buf[510];
	if (!file.is_open())
	{
		msg = ":MOTD File is missing";
		cmd->queue(ERR_NOMOTD, msg);
		return ;
	}
	while (!file.eof())
	{
		file.getline(buf, sizeof(buf));
		msg = ": - ";
		msg += buf;
		cmd->queue(RPL_MOTD, msg);
	}
	msg = ":End of /MOTD command";
	cmd->queue(RPL_ENDOFMOTD, msg);
}
