#ifndef __PORTCONNECTIONS_HPP__
# define __PORTCONNECTIONS_HPP__

# include <iostream>
# include <string>

// P:<Internet IP#>:<*>:<Internet IP Mask>:<Port>:
// P:<Directory>:<*>:<*>:<Port>:
namespace irc
{
	class PortConnections
	{
		private:
			std::string	_ip;
			std::string	_mask;
			int			_port;

		public:
			const std::string& get_ip();
			const std::string& get_mask();
			int get_port();

			void set_ip(std::string& ip);
			void set_mask(std::string& mask);
			void set_port(int port);

			void set_member(std::string& ip, std::string& mask, int port);
			void print();
	};
}
#endif