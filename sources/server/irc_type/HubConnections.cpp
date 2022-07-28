#include "HubConnections.hpp"

// public func
namespace irc
{
	const std::string& HubConnections::getServerMask() const
	{
		return _server_mask;
	}
	const std::string& HubConnections::getServerName() const
	{
		return _server_name;
	}

	void HubConnections::setServerMask(std::string& server_mask)
	{
		_server_mask = server_mask;
	}
	void HubConnections::setServerName(std::string& server_name)
	{
		_server_name = server_name;
	}

	void HubConnections::setMember(std::string& server_mask, std::string& server_name)
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
