#ifndef __ADMINISTRATIVEINFO_HPP__
# define __ADMINISTRATIVEINFO_HPP__

# include <iostream>
# include <string>

// A:<Your Name/Location>:<Your Electronic Mailing Addr>:<other>::
namespace irc
{
	class AdministrativeInfo
	{
		private:
			std::string	_name;           // 0
			std::string	_mailing_addr;   // 1
			std::string	_other;          // 2

		public:
			const std::string& get_name();
			const std::string& get_mailing_addr();
			const std::string& get_other();

			void set_name(std::string& name);
			void set_mailing_addr(std::string& mailing_addr);
			void set_other(std::string& other);

			void set_member(std::string& name, std::string& mailing_addr,
				std::string& other);

			void print();
	};
}

#endif