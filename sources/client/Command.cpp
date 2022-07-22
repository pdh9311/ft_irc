#include "Command.hpp"

namespace irc
{
	Command::Command(const std::string& p, const std::string& c, 
											const std::vector<std::string>& a)
	:	_prefix(p), _command(c), _args(a)
	{}

	Command::~Command()
	{}
}