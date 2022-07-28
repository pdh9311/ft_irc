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
			const std::string& get_server_mask();
			void set_server_mask(std::string& _server_mask);

			const std::string& get_server_name();
			void set_server_name(std::string& _server_name);

			const int get_max_depth();
			void set_max_depth(int _max_depth);

			void set_member(
				std::string _server_mask,
				std::string _server_name,
				int _max_depth
			);
			void print();
	};
}
#endif