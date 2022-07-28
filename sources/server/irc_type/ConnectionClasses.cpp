#include "ConnectionClasses.hpp"

// public func
namespace irc
{
	const int ConnectionClasses::get_class()
	{
		return _clazz;
	}

	void ConnectionClasses::set_class(int clazz)
	{
		_clazz = clazz;
	}

	const int ConnectionClasses::get_ping_frequency()
	{
		return _ping_frequency;
	}

	void ConnectionClasses::set_ping_frequency(int ping_frequency)
	{
		_ping_frequency = ping_frequency;
	}

	const int ConnectionClasses::get_connect_freq()
	{
		return _connect_freq;
	}

	void ConnectionClasses::set_connect_freq(int connect_freq)
	{
		_connect_freq = connect_freq;
	}

	const int ConnectionClasses::get_max_links()
	{
		return _max_links;
	}

	void ConnectionClasses::set_max_links(int max_links)
	{
		_max_links = max_links;
	}

	const int ConnectionClasses::get_sendQ()
	{
		return _sendQ;
	}

	void ConnectionClasses::set_sendQ(int sendQ)
	{
		_sendQ = sendQ;
	}

	const int ConnectionClasses::get_local_limit()
	{
		return _local_limit;
	}

	void ConnectionClasses::set_local_limit(int local_limit)
	{
		_local_limit = local_limit;
	}

	const int ConnectionClasses::get_global_Limit()
	{
		return _global_Limit;
	}

	void ConnectionClasses::set_global_Limit(int global_Limit)
	{
		_global_Limit = global_Limit;
	}

	void ConnectionClasses::set_member(
				int	clazz,         int ping_frequency,
				int connect_freq,  int max_links,
				int sendQ,         int local_limit,
				int global_Limit)
	{
		_clazz = clazz;
		_ping_frequency = ping_frequency;
		_connect_freq = connect_freq;
		_max_links = max_links;
		_sendQ = sendQ;
		_local_limit = local_limit;
		_global_Limit = global_Limit;
	}

	void ConnectionClasses::print()
	{
		std::cout << _clazz << " | ";
		std::cout << _ping_frequency << " | ";
		std::cout << _connect_freq << " | ";
		std::cout << _max_links << " | ";
		std::cout << _sendQ << " | ";
		std::cout << _local_limit << " | ";
		std::cout << _global_Limit << std::endl;
	}
}