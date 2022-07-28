#ifndef __DENYAUTOCONNECTIONS_HPP__
# define __DENYAUTOCONNECTIONS_HPP__

# include <iostream>
# include <string>

// D:<Denied Server Mask>:Denied Class:<Server Name>:Server Class:
namespace irc
{
	class DenyAutoConnections
	{
		private:
			std::string _denied_server_mask;
			std::string _denied_class;
			std::string _server_name;
			std::string _server_class;
		public:
			const std::string& get_denied_server_mask();
			void set_denied_server_mask(std::string& _denied_server_mask);

			const std::string& get_denied_class();
			void set_denied_class(std::string& _denied_class);

			const std::string& get_server_name();
			void set_server_name(std::string& _server_name);

			const std::string& get_server_class();
			void set_server_class(std::string& _server_class);

			void set_member(
				std::string _denied_server_mask,
				std::string _denied_class,
				std::string _server_name,
				std::string _server_class
			);
			void print();
	};
}
#endif