#ifndef __OPERATORPRIVILEGES_HPP__
# define __OPERATORPRIVILEGES_HPP__

# include <iostream>
# include <string>

// O:<TARGET Host NAME>:<Password>:<Nickname>:<Port>:<Class>
namespace irc
{
	class OperatorPrivileges
	{
		private:
			std::string _host_name;
			std::string _password;
			std::string _nickname;
			int _port; // NOT USED
			std::string _class;

		public:

			const std::string& get_host_name();
			void set_host_name(std::string& _host_name);

			const std::string& get_password();
			void set_password(std::string& _password);

			const std::string& get_nickname();
			void set_nickname(std::string& _nickname);

			const std::string& get_class();
			void set_class(std::string& _class);

			const int get_port();
			void set_port(int _port);

			void set_member(
				std::string _host_name,
				std::string _password,
				std::string _nickname,
				int _port,
				std::string _class
			);
			void print();
	};
}
#endif
