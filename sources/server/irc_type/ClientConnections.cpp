#include "ClientConnections.hpp"

// public func
namespace irc
{
	const std::string& ClientConnections::getHostAddr() const
	{
		return _host_addr;
	}
	const std::string& ClientConnections::getPassword() const
	{
		return _password;
	}
	const std::string& ClientConnections::getHostName() const
	{
		return _host_name;
	}
	int ClientConnections::getPort() const
	{
		return _port;
	}
	const std::string& ClientConnections::getClazz() const
	{
		return _clazz;
	}

	void ClientConnections::setHostAddr(std::string& host_addr)
	{
		_host_addr = host_addr;
	}
	void ClientConnections::setPassword(std::string& password)
	{
		_password = password;
	}
	void ClientConnections::setHostName(std::string& host_name)
	{
		_host_name = host_name;
	}
	void ClientConnections::setPort(int port)
	{
		_port = port;
	}
	void ClientConnections::setClazz(std::string& clazz)
	{
		_clazz = clazz;
	}

	void ClientConnections::setMember(std::string& host_addr, std::string& password,
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
