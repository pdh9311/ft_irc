#include "MachineInfo.hpp"

// public func
namespace irc
{
	const std::string& MachineInfo::get_server_name()
	{
		return _server_name;
	}

	const std::string& MachineInfo::get_ip()
	{
		return _ip;
	}

	const std::string& MachineInfo::get_location()
	{
		return _location;
	}

	int MachineInfo::get_port()
	{
		return _port;
	}

	void MachineInfo::set_server_name(std::string& server_name)
	{
		_server_name = server_name;
	}

	void MachineInfo::set_ip(std::string& ip)
	{
		_ip = ip;
	}

	void MachineInfo::set_location(std::string& location)
	{
		_location = location;
	}

	void MachineInfo::set_port(int port)
	{
		_port = port;
	}

	void MachineInfo::set_member(std::string& server_name, std::string& ip,
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