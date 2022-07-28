#include "VersionLimitations.hpp"

// public func
namespace irc
{
	const std::string& VersionLimitations::get_version_mask()
	{
		return _version_mask;
	}
	const std::string& VersionLimitations::get_flags()
	{
		return _flags;
	}
	const std::string& VersionLimitations::get_server_mask()
	{
		return _server_mask;
	}

	void VersionLimitations::set_version_mask(std::string& version_mask)
	{
		_version_mask = version_mask;
	}
	void VersionLimitations::set_flags(std::string& flags)
	{
		_flags = flags;
	}
	void VersionLimitations::set_server_mask(std::string& server_mask)
	{
		_server_mask = server_mask;
	}

	void VersionLimitations::set_member(std::string& version_mask, std::string& flags, std::string& server_mask)
	{
		_version_mask = version_mask;
		_flags = flags;
		_server_mask = server_mask;
	}

	void VersionLimitations::print()
	{
		std::cout << _version_mask << " | ";
		std::cout << _flags << " | ";
		std::cout << _server_mask << std::endl;
	}
}