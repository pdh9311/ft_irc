#include "ExcludedAccounts.hpp"

// public func
namespace irc
{
	const std::string& ExcludedAccounts::getHostName() const
	{
		return _host_name;
	}

	void ExcludedAccounts::setHostName(std::string &host_name)
	{
		_host_name = host_name;
	}

	const std::string& ExcludedAccounts::getTimeInterval() const
	{
		return _time_interval;
	}

	void ExcludedAccounts::setTimeInterval(std::string &time_interval)
	{
		_time_interval = time_interval;
	}

	const std::string& ExcludedAccounts::getAuth() const
	{
		return _auth;
	}

	void ExcludedAccounts::setAuth(std::string &auth)
	{
		_auth = auth;
	}

	int ExcludedAccounts::getPort() const
	{
		return _port;
	}

	void ExcludedAccounts::setPort(int port)
	{
		_port = port;
	}

	void ExcludedAccounts::setMember(
		std::string host_name, std::string time_interval,
		std::string auth, int port)
	{
		_host_name      = host_name;
		_time_interval  = time_interval;
		_auth           = auth;
		_port           = port;
	}

	void ExcludedAccounts::print()
	{
		std::cout << _host_name << " | ";
		std::cout << _time_interval << " | ";
		std::cout << _auth << " | ";
		std::cout << _port << std::endl;
	}
}
