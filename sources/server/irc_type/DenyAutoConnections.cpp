#include "DenyAutoConnections.hpp"

// public func
namespace irc
{
	const std::string& DenyAutoConnections::getDeniedServerMask() const
	{
		return _denied_server_mask;
	}

	void DenyAutoConnections::setDeniedServerMask(std::string &denied_server_mask)
	{
		_denied_server_mask = denied_server_mask;
	}

	const std::string& DenyAutoConnections::getDeniedClass() const
	{
		return _denied_class;
	}

	void DenyAutoConnections::setDeniedClass(std::string &denied_class)
	{
		_denied_class = denied_class;
	}

	const std::string& DenyAutoConnections::getServerName() const
	{
		return _server_name;
	}

	void DenyAutoConnections::setServerName(std::string &server_name)
	{
		_server_name = server_name;
	}

	const std::string& DenyAutoConnections::getServerClass() const
	{
		return _server_class;
	}

	void DenyAutoConnections::setServerClass(std::string &server_class)
	{
		_server_class = server_class;
	}

	void DenyAutoConnections::setMember(
			std::string denied_server_mask,
			std::string denied_class,
			std::string server_name,
			std::string server_class)
	{
		_denied_server_mask   =    denied_server_mask;
		_denied_class         =    denied_class;
		_server_name          =    server_name;
		_server_class         =    server_class;
	}

	void DenyAutoConnections::print()
	{
		std::cout << _denied_server_mask << " | ";
		std::cout << _denied_class << " | ";
		std::cout << _server_name << " | ";
		std::cout << _server_class << std::endl;
	}
}
