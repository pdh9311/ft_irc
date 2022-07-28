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

		const std::string& getHostName() const;
		void setHostName(std::string& host_name);

		const std::string& getTimeInterval() const;
		void setTimeInterval(std::string& time_interval);

		const std::string& getAuth() const;
		void setAuth(std::string& auth);

		int getPort() const;
		void setPort(int port);

		void setMember(
			std::string host_name,
			std::string time_interval,
			std::string auth,
			int port
		);
		void print();
	};
}
#endif
