#include "LeafConnections.hpp"

// public func
namespace irc
{
	const std::string& LeafConnections::getServerMask() const
	{
		return _server_mask;
	}

	void LeafConnections::setServerMask(std::string &server_mask)
	{
		_server_mask = server_mask;
	}

	const std::string& LeafConnections::getServerName() const
	{
		return _server_name;
	}

	void LeafConnections::setServerName(std::string &server_name)
	{
		_server_name = server_name;
	}

	int LeafConnections::getMaxDepth() const
	{
		return _max_depth;
	}

	void LeafConnections::setMaxDepth(int max_depth)
	{
		_max_depth = max_depth;
	}

	void LeafConnections::setMember(
			std::string server_mask,
			std::string server_name,
			int max_depth)
	{
			_server_mask  =  server_mask;
			_server_name  =  server_name;
			_max_depth    =  max_depth;
	}

	void LeafConnections::print()
	{
			std::cout << _server_mask << " | ";
			std::cout << _server_name << " | ";
			std::cout << _max_depth << std::endl;
	}
}
