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
		return (1);
	}
	std::string port(argv[1]);
	std::string password(argv[2]);
	if (port.empty() || password.empty())
	{
		std::cout << "port or password is empty" << std::endl;
		return (1);
	}
	int	iport = irc::stoi(port);
	if (iport <= 0)
	{
		std::cout << "invalid port" << std::endl;
		return (1);
	}
	irc::Server	serv(port, password);

	serv.initialize();
	serv.run();

	return (0);
}
