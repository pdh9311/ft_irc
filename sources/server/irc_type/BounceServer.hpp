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

		const std::string& get_class_host_mask();
		void set_class_host_mask(std::string& class_host_mask);

		const std::string& get_server_name();
		void set_server_name(std::string& server_name);

		const int get_port();
		void set_port(int port);

		void set_member(
			std::string class_host_mask,
			std::string server_name,
			int port
		);

		void print();
	};
}

#endif