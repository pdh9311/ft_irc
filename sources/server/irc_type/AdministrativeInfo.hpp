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
			const std::string& getName() const;
			const std::string& getMailingAddr() const;
			const std::string& getOther() const;

			void setName(std::string& name);
			void setMailingAddr(std::string& mailing_addr);
			void setOther(std::string& other);

			void setMember(std::string& name, std::string& mailing_addr,
				std::string& other);

			void print();
	};
}

#endif
