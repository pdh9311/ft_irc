#include "OperatorPrivileges.hpp"

// public func
namespace irc
{
	const std::string& OperatorPrivileges::getHostName() const
	{
		return _host_name;
	}

	void OperatorPrivileges::setHostName(std::string &host_name)
	{
		_host_name = host_name;
	}

	const std::string& OperatorPrivileges::getPassword() const
	{
		return _password;
	}

	void OperatorPrivileges::setPassword(std::string &password)
	{
		_password = password;
	}

	const std::string& OperatorPrivileges::getNickname() const
	{
		return _nickname;
	}

	void OperatorPrivileges::setNickname(std::string &nickname)
	{
		_nickname = nickname;
	}

	const std::string& OperatorPrivileges::getClazz() const
	{
		return _clazz;
	}

	void OperatorPrivileges::setClazz(std::string &clazz)
	{
		_clazz = clazz;
	}

	int OperatorPrivileges::getPort() const
	{
		return _port;
	}

	void OperatorPrivileges::setPort(int port)
	{
		_port = port;
	}

	void OperatorPrivileges::setMember(
		std::string host_name, std::string password,
		std::string nickname,  int port,
		std::string clazz)
	{
		_nickname  = nickname;
		_password  = password;
		_host_name = host_name;
		_clazz     = clazz;
		_port      = port;
	}

	void OperatorPrivileges::print()
	{
		std::cout << _nickname << " | ";
		std::cout << _password << " | ";
		std::cout << _host_name << " | ";
		std::cout << _clazz << " | ";
		std::cout << _port << std::endl;
	}
}
