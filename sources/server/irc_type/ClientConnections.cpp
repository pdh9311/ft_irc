#include "ClientConnections.hpp"

// public func
namespace irc
{
	const std::string& ClientConnections::get_host_addr()
	{
		return _host_addr;
	}
	const std::string& ClientConnections::get_password()
	{
		return _password;
	}
	const std::string& ClientConnections::get_host_name()
	{
		return _host_name;
	}
	int ClientConnections::get_port()
	{
		return _port;
	}
	const std::string& ClientConnections::get_class()
	{
		return _clazz;
	}

	void ClientConnections::set_host_addr(std::string& host_addr)
	{
		_host_addr = host_addr;
	}
	void ClientConnections::set_password(std::string& password)
	{
		_password = password;
	}
	void ClientConnections::set_host_name(std::string& host_name)
	{
		_host_name = host_name;
	}
	void ClientConnections::set_port(int port)
	{
		_port = port;
	}
	void ClientConnections::set_class(std::string& clazz)
	{
		_clazz = clazz;
	}

	void ClientConnections::set_member(std::string& host_addr, std::string& password,
		std::string& host_name, int port, std::string& clazz)
	{
		_host_addr = host_addr;
		_password = password;
		_host_name = host_name;
		_port = port;
		_clazz = clazz;
	}

	void ClientConnections::print()
	{
		std::cout << _host_addr << " | ";
		std::cout << _password << " | ";
		std::cout << _host_name << " | ";
		std::cout << _port << " | ";
		std::cout << _clazz << std::endl;

	}
}