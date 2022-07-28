#ifndef __DEFAULTLOCALSERVER_HPP__
# define __DEFAULTLOCALSERVER_HPP__

# include <iostream>
# include <string>

// U:<TARGET Host addr>:<Password>:<TARGET Host NAME>:<Internet Port>
namespace irc
{
	class DefaultLocalServer
	{
		private:
			std::string	_host_addr;
			std::string	_password;
			std::string	_host_name;
			int			_port;

		public:
			const std::string& get_host_addr();
			const std::string& get_password();
			const std::string& get_host_name();
			int get_port();

			void set_host_addr(std::string& host_addr);
			void set_password(std::string& password);
			void set_host_name(std::string& host_name);
			void set_port(int port);

			void set_member(std::string& host_addr, std::string& password,
							std::string& host_name, int port);
			void print();
	};
}
#endif