#include "PortConnections.hpp"

// public func
namespace irc
{
	const std::string& PortConnections::getIp() const
	{
		return _ip;
	}

	const std::string& PortConnections::getMask() const
	{
		return _mask;
	}

	int PortConnections::getPort() const
	{
		return _port;
	}

	void PortConnections::setIp(std::string& ip)
	{
		_ip = ip;
	}

	void PortConnections::setMask(std::string& mask)
	{
		_mask = mask;
	}

	void PortConnections::setPort(int port)
	{
		_port = port;
	}

	void PortConnections::setMember(std::string& ip, std::string& mask, int port)
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
