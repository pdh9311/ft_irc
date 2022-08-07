#include "server/Server.hpp"
#include "client/Command.hpp"
#include "util.hpp"
#include <iostream>
#include <string>

irc::Command::hashmap_t	irc::Command::hashmap = Command::build_hashmap();

int	main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return (0);
	}

	std::string portstr(argv[1]);
	if (portstr.empty())
	{
		std::cout << "port is empty" << std::endl;
		return (0);
	}
	int port = irc::stoi(portstr);
	if (portstr.size() != 5 || (port < 49152 || port > 65535))
	{
		std::cout << "port out of range (Please Use : 49152 ~ 65535) " << std::endl;
		return (0);
	}
	std::string password = argv[2];
	if (password.empty())
	{
		std::cout << "password is empty" << std::endl;
		return (0);
	}

	irc::Server	serv(argv[1], argv[2]);

	serv.initialize();
	serv.run();

	return (0);
}
