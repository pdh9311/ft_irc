#ifndef __CLIENTCONNECTIONS_HPP__
# define __CLIENTCONNECTIONS_HPP__

# include <iostream>
# include <string>

// I:<TARGET Host Addr>:<Password>:<TARGET Hosts NAME>:<Port>:<Class>
// i:<TARGET Host Addr>:<Password>:<TARGET Hosts NAME>:<Port>:<Class>
namespace irc
{
	class ClientConnections
	{
		private:
			std::string	_host_addr;
			std::string	_password;
			std::string	_host_name;
			int			_port;
			std::string	_clazz;

		public:
			const std::string& getHostAddr() const;
			const std::string& getPassword() const;
			const std::string& getHostName() const;
			int getPort() const;
			const std::string& getClazz() const;

			void setHostAddr(std::string& host_addr);
			void setPassword(std::string& password);
			void setHostName(std::string& host_name);
			void setPort(int port);
			void setClazz(std::string& clazz);

			void setMember(std::string& host_addr, std::string& password,
				std::string& host_name, int port, std::string& clazz);

			void print();
	};
}
#endif
