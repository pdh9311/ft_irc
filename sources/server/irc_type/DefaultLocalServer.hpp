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
			const std::string& getHostAddr() const;
			const std::string& getPassword() const;
			const std::string& getHostName() const;
			int getPort() const;

			void setHostAddr(std::string& host_addr);
			void setPassword(std::string& password);
			void setHostName(std::string& host_name);
			void setPort(int port);

			void setMember(std::string& host_addr, std::string& password,
							std::string& host_name, int port);
			void print();
	};
}
#endif
