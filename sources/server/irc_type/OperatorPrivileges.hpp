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
			std::string _clazz;

		public:

			const std::string& getHostName() const;
			void setHostName(std::string& host_name);

			const std::string& getPassword() const;
			void setPassword(std::string& password);

			const std::string& getNickname() const;
			void setNickname(std::string& nickname);

			const std::string& getClazz() const;
			void setClazz(std::string& clazz);

			int getPort() const;
			void setPort(int port);

			void setMember(
				std::string host_name,
				std::string password,
				std::string nickname,
				int port,
				std::string clazz
			);
			void print();
	};
}
#endif
