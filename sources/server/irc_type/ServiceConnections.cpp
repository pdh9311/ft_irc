#include "ServiceConnections.hpp"

// public func
namespace irc
{
	const std::string& ServiceConnections::get_host_mask()
	{
		return _host_mask;
	}
	const std::string& ServiceConnections::get_password()
	{
		return _password;
	}
	const std::string& ServiceConnections::get_service_name()
	{
		return _service_name;
	}
	const std::string& ServiceConnections::get_service_type()
	{
		return _service_type;
	}
	const std::string& ServiceConnections::get_clazz()
	{
		return _clazz;
	}

	void ServiceConnections::set_host_mask(std::string& host_mask)
	{
		_host_mask = host_mask;
	}
	void ServiceConnections::set_password(std::string& password)
	{
		_password = password;
	}
	void ServiceConnections::set_service_name(std::string& service_name)
	{
		_service_name = service_name;
	}
	void ServiceConnections::set_service_type(std::string& service_type)
	{
		_service_type = service_type;
	}
	void ServiceConnections::set_clazz(std::string& clazz)
	{
		_clazz = clazz;
	}

	void ServiceConnections::set_member(std::string& host_mask, std::string& password, std::string& service_name,
										std::string& service_type, std::string& clazz)
										{
		_host_mask = host_mask;
		_password = password;
		_service_name = service_name;
		_service_type = service_type;
		_clazz = clazz;
	}

	void ServiceConnections::print()
	{
		std::cout << _host_mask << " | ";
		std::cout << _password << " | ";
		std::cout << _service_name << " | ";
		std::cout << _service_type << " | ";
		std::cout << _clazz << std::endl;
	}
}