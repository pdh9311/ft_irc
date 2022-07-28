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
			const std::string& getHostName() const;
			const std::string& getProgram() const;
			const std::string& getUser() const;

			void setHostName(std::string& host_name);
			void setProgram(std::string& program);
			void setUser(std::string& user);

			void setMember(std::string& host_name, std::string& program, std::string& user);
			void print();
	};
}
#endif
