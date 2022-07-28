#include "LeafConnections.hpp"

// public func
namespace irc
{
	const std::string& LeafConnections::get_server_mask()
	{
		return _server_mask;
	}

	void LeafConnections::set_server_mask(std::string &_server_mask)
	{
		_server_mask = _server_mask;
	}

	const std::string& LeafConnections::get_server_name()
	{
		return _server_name;
	}

	void LeafConnections::set_server_name(std::string &_server_name)
	{
		_server_name = _server_name;
	}

	const int LeafConnections::get_max_depth()
	{
		return _max_depth;
	}

	void LeafConnections::set_max_depth(int _max_depth)
	{
		_max_depth = _max_depth;
	}

	void LeafConnections::set_member(
			std::string _server_mask,
			std::string _server_name,
			int _max_depth)
	{
			_server_mask  =  _server_mask;
			_server_name  =  _server_name;
			_max_depth    =  _max_depth;
	}

	void LeafConnections::print()
	{
			std::cout << _server_mask << " | ";
			std::cout << _server_name << " | ";
			std::cout << _max_depth << std::endl;
	}
}