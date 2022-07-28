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
			const std::string& getServerName() const;
			const std::string& getIp() const;
			const std::string& getLocation() const;
			int getPort() const;

			void setServerName(std::string& server_name);
			void setIp(std::string& ip);
			void setLocation(std::string& location);
			void setPort(int port);

			void setMember(std::string& server_name, std::string& ip,
							std::string& location, int port);
			void print();
	};
}
#endif
