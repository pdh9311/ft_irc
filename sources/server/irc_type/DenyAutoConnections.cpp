#include "DenyAutoConnections.hpp"

// public func
namespace irc
{
	const std::string& DenyAutoConnections::get_denied_server_mask()
	{
		return _denied_server_mask;
	}

	void DenyAutoConnections::set_denied_server_mask(std::string &_denied_server_mask)
	{
		_denied_server_mask = _denied_server_mask;
	}

	const std::string& DenyAutoConnections::get_denied_class()
	{
		return _denied_class;
	}

	void DenyAutoConnections::set_denied_class(std::string &_denied_class)
	{
		_denied_class = _denied_class;
	}

	const std::string& DenyAutoConnections::get_server_name()
	{
		return _server_name;
	}

	void DenyAutoConnections::set_server_name(std::string &_server_name)
	{
		_server_name = _server_name;
	}

	const std::string& DenyAutoConnections::get_server_class()
	{
		return _server_class;
	}

	void DenyAutoConnections::set_server_class(std::string &_server_class)
	{
		_server_class = _server_class;
	}

	void DenyAutoConnections::set_member(
			std::string _denied_server_mask,
			std::string _denied_class,
			std::string _server_name,
			std::string _server_class)
	{
		_denied_server_mask   =    _denied_server_mask;
		_denied_class         =    _denied_class;
		_server_name          =    _server_name;
		_server_class         =    _server_class;
	}

	void DenyAutoConnections::print()
	{
		std::cout << _denied_server_mask << " | ";
		std::cout << _denied_class << " | ";
		std::cout << _server_name << " | ";
		std::cout << _server_class << std::endl;
	}
}