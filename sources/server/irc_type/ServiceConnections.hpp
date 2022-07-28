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
			const std::string& get_host_mask();
			const std::string& get_password();
			const std::string& get_service_name();
			const std::string& get_service_type();
			const std::string& get_clazz();

			void set_host_mask(std::string& host_mask);
			void set_password(std::string& password);
			void set_service_name(std::string& service_name);
			void set_service_type(std::string& service_type);
			void set_clazz(std::string& clazz);

			void set_member(std::string& host_mask, std::string& password, std::string& service_name,
				std::string& service_type, std::string& clazz);
			void print();
	};
}
#endif