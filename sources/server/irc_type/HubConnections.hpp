#ifndef __HUBCONNECTIONS_HPP__
# define __HUBCONNECTIONS_HPP__

# include <iostream>
# include <string>

// H:<Server Mask>:*:<Server Name>::
namespace irc
{
	class HubConnections
	{
		private:
			std::string _server_mask;
			std::string _server_name;
		public:
			const std::string& getServerMask() const;
			const std::string& getServerName() const;

			void setServerMask(std::string& server_mask);
			void setServerName(std::string& server_name);

			void setMember(std::string& server_mask, std::string& server_name);
			void print();
	};
}
#endif
