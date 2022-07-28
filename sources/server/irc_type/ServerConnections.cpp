#include "ServerConnections.hpp"

// public func
namespace irc
{
	const std::string& ServerConnections::getHostAddr() const
	{
		return _host_addr;
	}
	const std::string& ServerConnections::getPassword() const
	{
		return _password;
	}
	const std::string& ServerConnections::getHostName() const
	{
		return _host_name;
	}
	int ServerConnections::getPort() const
	{
		return _port;
	}
	const std::string& ServerConnections::getClazz() const
	{
		return _clazz;
	}

	void ServerConnections::setHostAddr(std::string& host_addr)
	{
		_host_addr = host_addr;
	}
	void ServerConnections::setPassword(std::string& password)
	{
		_password = password;
	}
	void ServerConnections::setHostName(std::string& host_name)
	{
		_host_name = host_name;
	}
	void ServerConnections::setPort(int port)
	{
		_port = port;
	}
	void ServerConnections::setClazz(std::string& clazz)
	{
		_clazz = clazz;
	}

	void ServerConnections::setMember(std::string& host_addr, std::string& password,
		std::string& host_name, int port, std::string& clazz)
		{
		_host_addr = host_addr;
		_password = password;
		_host_name = host_name;
		_port = port;
		_clazz = clazz;
	}

	void ServerConnections::print()
	{
		std::cout << _host_addr << " | ";
		std::cout << _password << " | ";
		std::cout << _host_name << " | ";
		std::cout << _port << " | ";
		std::cout << _clazz << std::endl;
	}
}
