#ifndef __BOUNCESERVER_HPP__
# define __BOUNCESERVER_HPP__

# include <iostream>
# include <string>

// B:<Class|Host Mask>::<Server Name>:<Port>:
namespace irc
{
	class BounceServer
	{
		private:
			std::string _class_host_mask;
			std::string _server_name;
			int _port;
		public:

		const std::string& getClassHostMask() const;
		void setClassHostMask(std::string& class_host_mask);

		const std::string& getServerName() const;
		void setServerName(std::string& server_name);

		int getPort() const;
		void setPort(int port);

		void setMember(
			std::string class_host_mask,
			std::string server_name,
			int port
		);

		void print();
	};
}

#endif
