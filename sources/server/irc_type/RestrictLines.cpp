#include "RestrictLines.hpp"

// public func
namespace irc
{
	const std::string& RestrictLines::getHostName() const
	{
		return _host_name;
	}
	const std::string& RestrictLines::getProgram() const
	{
		return _program;
	}
	const std::string& RestrictLines::getUser() const
	{
		return _user;
	}

	void RestrictLines::setHostName(std::string& host_name)
	{
		_host_name = host_name;
	}
	void RestrictLines::setProgram(std::string& program)
	{
		_program = program;
	}
	void RestrictLines::setUser(std::string& user)
	{
		_user = user;
	}

	void RestrictLines::setMember(std::string& host_name, std::string& program, std::string& user)
	{
		_host_name = host_name;
		_program = program;
		_user = user;
	}

	void RestrictLines::print()
	{
		std::cout << _host_name << " | ";
		std::cout << _program << " | ";
		std::cout << _user << std::endl;
	}
}
