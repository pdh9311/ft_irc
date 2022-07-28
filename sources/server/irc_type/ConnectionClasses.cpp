#include "ConnectionClasses.hpp"

// public func
namespace irc
{
	const int ConnectionClasses::get_class()
	{
		return _class;
	}

	void ConnectionClasses::set_class(int _class)
	{
		_class = _class;
	}

	const int ConnectionClasses::get_ping_frequency()
	{
		return _ping_frequency;
	}

	void ConnectionClasses::set_ping_frequency(int _ping_frequency)
	{
		_ping_frequency = _ping_frequency;
	}

	const int ConnectionClasses::get_connect_freq()
	{
		return _connect_freq;
	}

	void ConnectionClasses::set_connect_freq(int _connect_freq)
	{
		_connect_freq = _connect_freq;
	}

	const int ConnectionClasses::get_max_links()
	{
		return _max_links;
	}

	void ConnectionClasses::set_max_links(int _max_links)
	{
		_max_links = _max_links;
	}

	const int ConnectionClasses::get_sendQ()
	{
		return _sendQ;
	}

	void ConnectionClasses::set_sendQ(int _sendQ)
	{
		_sendQ = _sendQ;
	}

	const int ConnectionClasses::get_local_limit()
	{
		return _local_limit;
	}

	void ConnectionClasses::set_local_limit(int _local_limit)
	{
		_local_limit = _local_limit;
	}

	const int ConnectionClasses::get_global_Limit()
	{
		return _global_Limit;
	}

	void ConnectionClasses::set_global_Limit(int _global_Limit)
	{
		_global_Limit = _global_Limit;
	}

	void ConnectionClasses::set_member(
				int	_class,         int _ping_frequency,
				int _connect_freq,  int _max_links,
				int _sendQ,         int _local_limit,
				int _global_Limit)
	{
		_class =_class;
		_ping_frequency = _ping_frequency;
		_connect_freq = _connect_freq;
		_max_links = _max_links;
		_sendQ = _sendQ;
		_local_limit = _local_limit;
		_global_Limit = _global_Limit;
	}
	void ConnectionClasses::print()
	{
		std::cout << _class << " | ";
		std::cout << _ping_frequency << " | ";
		std::cout << _connect_freq << " | ";
		std::cout << _max_links << " | ";
		std::cout << _sendQ << " | ";
		std::cout << _local_limit << " | ";
		std::cout << _global_Limit << std::endl;
	}
}