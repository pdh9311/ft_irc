#include "server/Server.hpp"
#include "client/Command.hpp"
#include "util.hpp"
#include <iostream>
#include <string>

irc::Command::hashmap_t	irc::Command::hashmap = Command::build_hashmap();

int	main(int argc, char** argv)
{
	if (argc < 2 || 3 < argc)
	{
		std::cout << "Usage: " << argv[0] << " <port> [password]" << std::endl;
		return (0);
	}

	irc::Server	serv(argv[1], (argv[2] == NULL ? "" : argv[2]));		

	serv.initialize();
	serv.run();
	return (0);
}
