#include "ConnectionClasses.hpp"

// public func
namespace irc
{
	int ConnectionClasses::getClazz() const
	{
		return _clazz;
	}

	void ConnectionClasses::setClazz(int clazz)
	{
		_clazz = clazz;
	}

	int ConnectionClasses::getPingFrequency() const
	{
		return _ping_frequency;
	}

	void ConnectionClasses::setPingFrequency(int ping_frequency)
	{
		_ping_frequency = ping_frequency;
	}

	int ConnectionClasses::getConnectFreq() const
	{
		return _connect_freq;
	}

	void ConnectionClasses::setConnectFreq(int connect_freq)
	{
		_connect_freq = connect_freq;
	}

	int ConnectionClasses::getMaxLinks() const
	{
		return _max_links;
	}

	void ConnectionClasses::setMaxLinks(int max_links)
	{
		_max_links = max_links;
	}

	int ConnectionClasses::getSendQ() const
	{
		return _sendQ;
	}

	void ConnectionClasses::setSendQ(int sendQ)
	{
		_sendQ = sendQ;
	}

	int ConnectionClasses::getLocalLimit() const
	{
		return _local_limit;
	}

	void ConnectionClasses::setLocalLimit(int local_limit)
	{
		_local_limit = local_limit;
	}

	int ConnectionClasses::getGlobalLimit() const
	{
		return _global_Limit;
	}

	void ConnectionClasses::setGlobalLimit(int global_Limit)
	{
		_global_Limit = global_Limit;
	}

	void ConnectionClasses::setMember(
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
