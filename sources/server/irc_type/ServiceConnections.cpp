#include "ServiceConnections.hpp"

// public func
namespace irc
{
	const std::string& ServiceConnections::getHostMask() const
	{
		return _host_mask;
	}
	const std::string& ServiceConnections::getPassword() const
	{
		return _password;
	}
	const std::string& ServiceConnections::getServiceName() const
	{
		return _service_name;
	}
	const std::string& ServiceConnections::getServiceType() const
	{
		return _service_type;
	}
	const std::string& ServiceConnections::getClazz() const
	{
		return _clazz;
	}

	void ServiceConnections::setHostMask(std::string& host_mask)
	{
		_host_mask = host_mask;
	}
	void ServiceConnections::setPassword(std::string& password)
	{
		_password = password;
	}
	void ServiceConnections::setServiceName(std::string& service_name)
	{
		_service_name = service_name;
	}
	void ServiceConnections::setServiceType(std::string& service_type)
	{
		_service_type = service_type;
	}
	void ServiceConnections::setClazz(std::string& clazz)
	{
		_clazz = clazz;
	}

	void ServiceConnections::setMember(std::string& host_mask, std::string& password, std::string& service_name,
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
