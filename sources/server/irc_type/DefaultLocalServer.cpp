#include "DefaultLocalServer.hpp"

// public func
namespace irc
{
	const std::string& DefaultLocalServer::get_host_addr()
	{
		return _host_addr;
	}
	const std::string& DefaultLocalServer::get_password()
	{
		return _password;
	}
	const std::string& DefaultLocalServer::get_host_name()
	{
		return _host_name;
	}
	int DefaultLocalServer::get_port()
	{
		return _port;
	}

	void DefaultLocalServer::set_host_addr(std::string& host_addr)
	{
		_host_addr = host_addr;
	}
	void DefaultLocalServer::set_password(std::string& password)
	{
		_password = password;
	}
	void DefaultLocalServer::set_host_name(std::string& host_name)
	{
		_host_name = host_name;
	}
	void DefaultLocalServer::set_port(int port)
	{
		_port = port;
	}

	void DefaultLocalServer::set_member(
		std::string& host_addr, std::string& password,
		std::string& host_name, int port)
	{
		_host_addr = host_addr;
		_password = password;
		_host_name = host_name;
		_port = port;
	}
	void DefaultLocalServer::print()
	{
		std::cout << _host_addr << " | ";
		std::cout << _password << " | ";
		std::cout << _host_name << " | ";
		std::cout << _port << std::endl;
	}
}