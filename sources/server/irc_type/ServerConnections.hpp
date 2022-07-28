#ifndef __SERVERCONNECTIONS_HPP__
# define __SERVERCONNECTIONS_HPP__

# include <iostream>
# include <string>

// C:<TARGET Host Addr>:<Password>:<TARGET Host NAME>:<TARGET PORT>:<Class>
namespace irc
{
	class ServerConnections
	{
		private:
			std::string	_host_addr;
			std::string	_password;
			std::string	_host_name;
			int			_port;
			std::string	_clazz;

		public:
			const std::string& get_host_addr();
			const std::string& get_password();
			const std::string& get_host_name();
			int get_port();
			const std::string& get_clazz();

			void set_host_addr(std::string& host_addr);
			void set_password(std::string& password);
			void set_host_name(std::string& host_name);
			void set_port(int port);
			void set_clazz(std::string& clazz);

			void set_member(std::string& host_addr, std::string& password,
				std::string& host_name, int port, std::string& clazz);
			void print();
	};
}
#endif