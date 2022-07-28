#include "PortConnections.hpp"

// public func
namespace irc
{
	const std::string& PortConnections::get_ip()
	{
		return _ip;
	}

	const std::string& PortConnections::get_mask()
	{
		return _mask;
	}

	int PortConnections::get_port()
	{
		return _port;
	}

	void PortConnections::set_ip(std::string& ip)
	{
		_ip = ip;
	}

	void PortConnections::set_mask(std::string& mask)
	{
		_mask = mask;
	}

	void PortConnections::set_port(int port)
	{
		_port = port;
	}

	void PortConnections::set_member(std::string& ip, std::string& mask, int port)
	{
		_ip = ip;
		_mask = mask;
		_port = port;
	}

	void PortConnections::print()
	{
		std::cout << _ip << " | ";
		std::cout << _mask << " | ";
		std::cout << _port << std::endl;
	}
}