#include "VersionLimitations.hpp"

// public func
namespace irc
{
	const std::string& VersionLimitations::getVersionMask() const
	{
		return _version_mask;
	}
	const std::string& VersionLimitations::getFlags() const
	{
		return _flags;
	}
	const std::string& VersionLimitations::getServerMask() const
	{
		return _server_mask;
	}

	void VersionLimitations::setVersionMask(std::string& version_mask)
	{
		_version_mask = version_mask;
	}
	void VersionLimitations::setFlags(std::string& flags)
	{
		_flags = flags;
	}
	void VersionLimitations::setServerMask(std::string& server_mask)
	{
		_server_mask = server_mask;
	}

	void VersionLimitations::setMember(std::string& version_mask, std::string& flags, std::string& server_mask)
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
