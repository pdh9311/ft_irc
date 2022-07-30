#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <set>
#include <string>

namespace irc
{
	class Server;
	class Client;

	class Channel
	{
		public:
			typedef std::set<int>	clients_t;
			typedef std::set<char>	modes_t;
			typedef std::set<int>	invites_t;

		private:
			Server*		_server;
			std::string	_name;
			bool		_is_local;
			std::string	_topic;
			clients_t	_clients;
			modes_t		_modes;
			invites_t	_invites;

		public:
			Channel(Server* server, const std::string name);
			~Channel();

			bool	isMember(const Client* client);
			bool	isMember(const int fd);
			bool	hasMode(const char c);
			void	addClient(const Client* client);
			void	rmClient(const Client* client);

			const std::string&	getName() const;
			const std::string	getFName() const;
			const std::string&	getTopic() const;
			const clients_t&	getClients() const;
			const modes_t&		getModes() const;
			std::string			getModestr() const;
			std::string			getMembers() const;
			size_t				getSize() const;

			void	setTopic(const std::string& topic);
			void	setModes(const std::string& modes);
			void	setMode(const char c);
			void	unsetModes(const std::string& modes);
			void	unsetMode(const char c);
			void	inviteMember(Client* client);
	};
}

#endif
