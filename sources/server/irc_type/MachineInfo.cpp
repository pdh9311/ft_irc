#include "MachineInfo.hpp"

// public func
namespace irc
{
	const std::string& MachineInfo::getServerName() const
	{
		return _server_name;
	}

	const std::string& MachineInfo::getIp() const
	{
		return _ip;
	}

	const std::string& MachineInfo::getLocation() const
	{
		return _location;
	}

	int MachineInfo::getPort() const
	{
		return _port;
	}

	void MachineInfo::setServerName(std::string& server_name)
	{
		_server_name = server_name;
	}

	void MachineInfo::setIp(std::string& ip)
	{
		_ip = ip;
	}

	void MachineInfo::setLocation(std::string& location)
	{
		_location = location;
	}

	void MachineInfo::setPort(int port)
	{
		_port = port;
	}

	void MachineInfo::setMember(std::string& server_name, std::string& ip,
									std::string& location, int port)
	{
		_server_name = server_name;
		_ip = ip;
		_location = location;
		_port = port;
	}

	void MachineInfo::print()
	{
		std::cout << _server_name << " | ";
		std::cout << _ip << " | ";
		std::cout << _location << " | ";
		std::cout << _port << std::endl;
	}
}
