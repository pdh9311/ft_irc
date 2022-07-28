#include "debug.hpp"
#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdlib>

// #include <unistd.h>
// #include <errno.h>

namespace irc
{
	int	x_int(int err, int res, std::string str, std::string file, int line)
	{
		if (res == err)
		{
			std::cerr << str << " error (" << file << ", " << line << "): ";
			std::cerr << std::strerror(errno) << std::endl;

			std::exit (1);
		}
		return (res);
	}

	void*	x_void(void* err, void* res, std::string str, std::string file,
																	int line)
	{
		if (res == err)
		{
			std::cerr << str << " error (" << file << ", " << line << "): ";
			std::cerr << std::strerror(errno) << std::endl;

			std::exit (1);
		}
		return (res);
	}

	void	x_line(std::string str, std::string file, int line)
	{
		std::cerr << str << " error (" << file << ", " << line << "): ";
		std::cerr << std::strerror(errno) << std::endl;
		std::exit (1);
	}

	void	perror(std::string err, std::string file, int line)
	{
		std::cerr << err  << " (" << file << ", " << line << ")" << std::endl;;
		std::exit (1);
	}
}
