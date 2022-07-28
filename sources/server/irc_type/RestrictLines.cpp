#include "RestrictLines.hpp"

// public func
namespace irc
{
	const std::string& RestrictLines::get_host_name()
	{
		return _host_name;
	}
	const std::string& RestrictLines::get_program()
	{
		return _program;
	}
	const std::string& RestrictLines::get_user()
	{
		return _user;
	}

	void RestrictLines::set_host_name(std::string& host_name)
	{
		_host_name = host_name;
	}
	void RestrictLines::set_program(std::string& program)
	{
		_program = program;
	}
	void RestrictLines::set_user(std::string& user)
	{
		_user = user;
	}

	void RestrictLines::set_member(std::string& host_name, std::string& program, std::string& user)
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