#include "BounceServer.hpp"

// public func
namespace irc
{
	const std::string& BounceServer::getClassHostMask() const
	{
		return _class_host_mask;
	}

	void BounceServer::setClassHostMask(std::string &class_host_mask)
	{
		_class_host_mask = class_host_mask;
	}

	const std::string& BounceServer::getServerName() const
	{
		return _server_name;
	}

	void BounceServer::setServerName(std::string &server_name)
	{
		_server_name = server_name;
	}

	int BounceServer::getPort() const
	{
		return _port;
	}

	void BounceServer::setPort(int port)
	{
		_port = port;
	}

	void BounceServer::setMember(
		std::string class_host_mask,
		std::string server_name,
		int port)
	{
		_class_host_mask  =   class_host_mask;
		_server_name      =   server_name;
		_port             =   port;
	}
	void BounceServer::print()
	{
		std::cout << _class_host_mask << " | ";
		std::cout << _server_name << " | ";
		std::cout << _port << std::endl;
	}
}
