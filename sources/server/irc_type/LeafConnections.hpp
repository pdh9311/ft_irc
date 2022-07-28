#ifndef __LEAFCONNECTIONS_HPP__
# define __LEAFCONNECTIONS_HPP__

# include <iostream>
# include <string>

// L:<Server Mask>:*:<Server Name>:<Max Depth>:
namespace irc
{
	class LeafConnections
	{
		private:
			std::string _server_mask;
			std::string _server_name;
			int _max_depth;
		public:
			const std::string& getServerMask() const;
			void setServerMask(std::string& server_mask);

			const std::string& getServerName() const;
			void setServerName(std::string& server_name);

			int getMaxDepth() const;
			void setMaxDepth(int max_depth);

			void setMember(
				std::string server_mask,
				std::string server_name,
				int max_depth
			);
			void print();
	};
}
#endif
