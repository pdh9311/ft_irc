#include "ExcludedAccounts.hpp"

// public func
namespace irc
{
	const std::string& ExcludedAccounts::get_host_name()
	{
		return _host_name;
	}

	void ExcludedAccounts::set_host_name(std::string &host_name)
	{
		_host_name = host_name;
	}

	const std::string& ExcludedAccounts::get_time_interval()
	{
		return _time_interval;
	}

	void ExcludedAccounts::set_time_interval(std::string &time_interval)
	{
		_time_interval = time_interval;
	}

	const std::string& ExcludedAccounts::get_auth()
	{
		return _auth;
	}

	void ExcludedAccounts::set_auth(std::string &auth)
	{
		_auth = auth;
	}

	const int ExcludedAccounts::get_port()
	{
		return _port;
	}

	void ExcludedAccounts::set_port(int port)
	{
		_port = port;
	}

	void ExcludedAccounts::set_member(
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