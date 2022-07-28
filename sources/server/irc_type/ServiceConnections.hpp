#ifndef __SERVICECONNECTIONS_HPP__
# define __SERVICECONNECTIONS_HPP__

# include <iostream>
# include <string>

// S:<TARGET Host Mask>:<Password>:<Service Name>:<Service Type>:<Class>
namespace irc
{
	class ServiceConnections
	{
		private:
			std::string _host_mask;
			std::string _password;
			std::string _service_name;
			std::string _service_type;
			std::string _clazz;

		public:
			const std::string& getHostMask() const;
			const std::string& getPassword() const;
			const std::string& getServiceName() const;
			const std::string& getServiceType() const;
			const std::string& getClazz() const;

			void setHostMask(std::string& host_mask);
			void setPassword(std::string& password);
			void setServiceName(std::string& service_name);
			void setServiceType(std::string& service_type);
			void setClazz(std::string& clazz);

			void setMember(std::string& host_mask, std::string& password, std::string& service_name,
				std::string& service_type, std::string& clazz);
			void print();
	};
}
#endif
