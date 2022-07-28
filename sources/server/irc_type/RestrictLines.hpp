#ifndef __RESTRICTLINES_HPP__
# define __RESTRICTLINES_HPP__

# include <iostream>
# include <string>

// R:<Target Host Name>:<Program>:<User>:::
namespace irc
{
	class RestrictLines
	{
		private:
			std::string	_host_name;
			std::string	_program;
			std::string	_user;

		public:
			const std::string& get_host_name();
			const std::string& get_program();
			const std::string& get_user();

			void set_host_name(std::string& host_name);
			void set_program(std::string& program);
			void set_user(std::string& user);

			void set_member(std::string& host_name, std::string& program, std::string& user);
			void print();
	};
}
#endif