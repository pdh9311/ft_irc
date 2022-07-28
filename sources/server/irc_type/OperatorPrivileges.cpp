#include "OperatorPrivileges.hpp"

// public func
namespace irc
{
	const std::string& OperatorPrivileges::get_host_name()
	{
		return _host_name;
	}

	void OperatorPrivileges::set_host_name(std::string &_host_name)
	{
		_host_name = _host_name;
	}

	const std::string& OperatorPrivileges::get_password()
	{
		return _password;
	}

	void OperatorPrivileges::set_password(std::string &_password)
	{
		_password = _password;
	}

	const std::string& OperatorPrivileges::get_nickname()
	{
		return _nickname;
	}

	void OperatorPrivileges::set_nickname(std::string &_nickname)
	{
		_nickname = _nickname;
	}

	const std::string& OperatorPrivileges::get_class()
	{
		return _class;
	}

	void OperatorPrivileges::set_class(std::string &_class)
	{
		_class = _class;
	}

	const int OperatorPrivileges::get_port()
	{
		return _port;
	}

	void OperatorPrivileges::set_port(int _port)
	{
		_port = _port;
	}

	void OperatorPrivileges::set_member(
		std::string _host_name, std::string _password,
		std::string _nickname,  int _port,
		std::string _class)
	{
		_nickname  = _nickname;
		_password  = _password;
		_host_name = _host_name;
		_class     = _class;
		_port      = _port;
	}

	void OperatorPrivileges::print()
	{
		std::cout << _nickname << " | ";
		std::cout << _password << " | ";
		std::cout << _host_name << " | ";
		std::cout << _class << " | ";
		std::cout << _port << std::endl;
	}
}