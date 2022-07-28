#ifndef __VERSIONLIMITATIONS_HPP__
# define __VERSIONLIMITATIONS_HPP__

# include <iostream>
# include <string>

// V:<Version Mask>:<Flags>:<Server Mask>::
namespace irc
{
	class VersionLimitations
	{
		private:
			std::string _version_mask;
			std::string _flags;
			std::string _server_mask;

		public:
			const std::string& get_version_mask();
			const std::string& get_flags();
			const std::string& get_server_mask();

			void set_version_mask(std::string& version_mask);
			void set_flags(std::string& flags);
			void set_server_mask(std::string& server_mask);

			void set_member(std::string& version_mask, std::string& flags, std::string& server_mask);

			void print();
	};
}
#endif