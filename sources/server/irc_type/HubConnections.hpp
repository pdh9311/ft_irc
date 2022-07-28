#ifndef __HUBCONNECTIONS_HPP__
# define __HUBCONNECTIONS_HPP__

# include <iostream>
# include <string>

// H:<Server Mask>:*:<Server Name>::
namespace irc
{
	class HubConnections
	{
		private:
			std::string _server_mask;
			std::string _server_name;
		public:
			const std::string& get_server_mask();
			const std::string& get_server_name();

			void set_server_mask(std::string& server_mask);
			void set_server_name(std::string& server_name);

			void set_member(std::string& server_mask, std::string& server_name);
			void print();
	};
}
#endif