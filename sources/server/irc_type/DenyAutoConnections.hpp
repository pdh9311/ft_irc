#ifndef __DENYAUTOCONNECTIONS_HPP__
# define __DENYAUTOCONNECTIONS_HPP__

# include <iostream>
# include <string>

// D:<Denied Server Mask>:Denied Class:<Server Name>:Server Class:
namespace irc
{
	class DenyAutoConnections
	{
		private:
			std::string _denied_server_mask;
			std::string _denied_class;
			std::string _server_name;
			std::string _server_class;
		public:
			const std::string& getDeniedServerMask() const;
			void setDeniedServerMask(std::string& denied_server_mask);

			const std::string& getDeniedClass() const;
			void setDeniedClass(std::string& denied_class);

			const std::string& getServerName() const;
			void setServerName(std::string& server_name);

			const std::string& getServerClass() const;
			void setServerClass(std::string& server_class);

			void setMember(
				std::string denied_server_mask,
				std::string denied_class,
				std::string server_name,
				std::string server_class
			);
			void print();
	};
}
#endif
