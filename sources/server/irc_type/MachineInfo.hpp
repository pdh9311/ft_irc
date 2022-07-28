#ifndef __MACHINEINFO_HPP__
# define __MACHINEINFO_HPP__

# include <iostream>
# include <string>

// M:<Server NAME>:<YOUR Internet IP#>:<Geographic Location>:<Port>
namespace irc
{
	class MachineInfo
	{
		private:
			std::string _server_name;
			std::string _ip;
			std::string _location;
			int _port;

		public:
			const std::string& get_server_name();
			const std::string& get_ip();
			const std::string& get_location();
			int get_port();

			void set_server_name(std::string& server_name);
			void set_ip(std::string& ip);
			void set_location(std::string& location);
			void set_port(int port);

			void set_member(std::string& server_name, std::string& ip,
							std::string& location, int port);
			void print();
	};
}
#endif