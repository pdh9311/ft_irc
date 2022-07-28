#include "BounceServer.hpp"

// public func
namespace irc
{
	const std::string& BounceServer::get_class_host_mask()
	{
		return _class_host_mask;
	}

	void BounceServer::set_class_host_mask(std::string &class_host_mask)
	{
		_class_host_mask = class_host_mask;
	}

	const std::string& BounceServer::get_server_name()
	{
		return _server_name;
	}

	void BounceServer::set_server_name(std::string &server_name)
	{
		_server_name = server_name;
	}

	const int BounceServer::get_port()
	{
		return _port;
	}

	void BounceServer::set_port(int port)
	{
		_port = port;
	}

	void BounceServer::set_member(
		std::string class_host_mask,
		std::string server_name,
		int port)
	{
		_class_host_mask  =   class_host_mask;
		_server_name    =   server_name;
		_port    =   port;
	}
	void BounceServer::print()
	{
		std::cout << _class_host_mask << " | ";
		std::cout << _server_name << " | ";
		std::cout << _port << std::endl;
	}
}