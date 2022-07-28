#include "AdministrativeInfo.hpp"

// public func
namespace irc
{
	const std::string& AdministrativeInfo::get_name()
	{
		return _name;
	}
	const std::string& AdministrativeInfo::get_mailing_addr()
	{
		return _mailing_addr;
	}
	const std::string& AdministrativeInfo::get_other()
	{
		return _other;
	}

	void AdministrativeInfo::set_name(std::string &name)
	{
		_name = name;
	}
	void AdministrativeInfo::set_mailing_addr(std::string &password)
	{
		_mailing_addr = password;
	}
	void AdministrativeInfo::set_other(std::string &other)
	{
		_other = other;
	}

	void AdministrativeInfo::set_member(std::string &name, std::string &password, std::string &other)
	{
		_name = name;
		_mailing_addr = password;
		_other = other;
	}
	void AdministrativeInfo::print()
	{
		std::cout << _name << " | ";
		std::cout << _mailing_addr << " | ";
		std::cout << _other << std::endl;
	}
}