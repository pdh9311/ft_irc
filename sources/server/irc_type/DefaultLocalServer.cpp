#include "DefaultLocalServer.hpp"

// public func
namespace irc
{
	const std::string& DefaultLocalServer::getHostAddr() const
	{
		return _host_addr;
	}
	const std::string& DefaultLocalServer::getPassword() const
	{
		return _password;
	}
	const std::string& DefaultLocalServer::getHostName() const
	{
		return _host_name;
	}
	int DefaultLocalServer::getPort() const
	{
		return _port;
	}

	void DefaultLocalServer::setHostAddr(std::string& host_addr)
	{
		_host_addr = host_addr;
	}
	void DefaultLocalServer::setPassword(std::string& password)
	{
		_password = password;
	}
	void DefaultLocalServer::setHostName(std::string& host_name)
	{
		_host_name = host_name;
	}
	void DefaultLocalServer::setPort(int port)
	{
		_port = port;
	}

	void DefaultLocalServer::setMember(
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
