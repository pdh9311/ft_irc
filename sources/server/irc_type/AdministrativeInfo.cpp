#include "AdministrativeInfo.hpp"

// public func
namespace irc
{
	const std::string& AdministrativeInfo::getName() const
	{
		return _name;
	}
	const std::string& AdministrativeInfo::getMailingAddr() const
	{
		return _mailing_addr;
	}
	const std::string& AdministrativeInfo::getOther() const
	{
		return _other;
	}

	void AdministrativeInfo::setName(std::string &name)
	{
		_name = name;
	}
	void AdministrativeInfo::setMailingAddr(std::string &password)
	{
		_mailing_addr = password;
	}
	void AdministrativeInfo::setOther(std::string &other)
	{
		_other = other;
	}

	void AdministrativeInfo::setMember(std::string &name, std::string &password, std::string &other)
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
