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
			const std::string& getIp() const;
			const std::string& getMask() const;
			int getPort() const;

			void setIp(std::string& ip);
			void setMask(std::string& mask);
			void setPort(int port);

			void setMember(std::string& ip, std::string& mask, int port);
			void print();
	};
}
#endif
