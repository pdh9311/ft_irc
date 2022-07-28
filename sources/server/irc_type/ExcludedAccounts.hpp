#ifndef __EXCLUDEDACCOUNTS_HPP__
# define __EXCLUDEDACCOUNTS_HPP__

# include <iostream>
# include <string>

// K:<Host Name>:<time interval(s)|comment>:<User>:<port>:
// k:<Host Name>:<time interval(s)|comment>:<Auth>:<port>:
namespace irc
{
	class ExcludedAccounts
	{
		private:
			std::string _host_name;
			std::string _time_interval;
			std::string _auth;
			int _port;
		public:

		const std::string& get_host_name();
		void set_host_name(std::string& host_name);

		const std::string& get_time_interval();
		void set_time_interval(std::string& time_interval);

		const std::string& get_auth();
		void set_auth(std::string& auth);

		const int get_port();
		void set_port(int port);

		void set_member(
			std::string host_name,
			std::string time_interval,
			std::string auth,
			int port
		);
		void print();
	};
}
#endif