#include "HubConnections.hpp"

// public func
namespace irc
{
	const std::string& HubConnections::get_server_mask()
	{
		return _server_mask;
	}
	const std::string& HubConnections::get_server_name()
	{
		return _server_name;
	}

	void HubConnections::set_server_mask(std::string& server_mask)
	{
		_server_mask = server_mask;
	}
	void HubConnections::set_server_name(std::string& server_name)
	{
		_server_name = server_name;
	}

	void HubConnections::set_member(std::string& server_mask, std::string& server_name)
	{
		_server_mask = server_mask;
		_server_name = server_name;
	}

	void HubConnections::print()
	{
		std::cout << _server_mask << " | ";
		std::cout << _server_name << std::endl;
	}
}