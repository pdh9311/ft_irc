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
			const std::string& getVersionMask() const;
			const std::string& getFlags() const;
			const std::string& getServerMask() const;

			void setVersionMask(std::string& version_mask);
			void setFlags(std::string& flags);
			void setServerMask(std::string& server_mask);

			void setMember(std::string& version_mask, std::string& flags, std::string& server_mask);

			void print();
	};
}
#endif
