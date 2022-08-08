#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <set>
#include <map>
#include <string>

namespace irc
{
	class Server;
	class Client;

	class Channel
	{
		public:
			typedef std::set<int>					clients_t;
			typedef std::set<char>					modes_t;
			typedef std::set<int>					invites_t;
			typedef std::map<int, std::set<char> >	umodes_t;

		private:
			Server*		_server;
			std::string	_name;
			char		_prefix;
			std::string	_key;
			// bool		_is_local;
			size_t		_max_client;
			std::string	_topic;
			clients_t	_clients;
			modes_t		_modes;
			umodes_t	_user_modes;
			invites_t	_invites;
			
		public:
			Channel(Server* server, const std::string name);
			~Channel();

			void	sendNames(const Client* client) const;
			void	broadcast(const Client* client, const std::string msg) const;
			bool	isInvited(const Client* client) const;
			bool	isMember(const Client* client) const;
			bool	isMember(const int fd) const;
			bool	hasMode(const char c) const;
			bool	hasUserMode(const Client* client, const char c) const;
			void	addClient(const Client* client);
			void	rmClient(const Client* client);

			char				getPrefix() const;
			const std::string&	getName() const;
			const std::string	getFName() const;
			const std::string&	getTopic() const;
			const std::string&	getKey() const;
			const clients_t&	getClients() const;
			const modes_t&		getModes() const;
			std::string			getModestr() const;
			const modes_t&		getUserModes(Client* client);
			std::string			getUserModestr(Client* client) const;
			std::string			getMembers() const;
			size_t				getSize() const;
			const size_t&		getMaxClient() const;

			void	setMaxClient(size_t max);
			void	setKey(const std::string& key);
			void	setTopic(const std::string& topic);
			void	setModes(const std::string& modes);
			void	setMode(const char c);
			void	setUserModes(Client* client, const std::string& modes);
			void	setUserMode(Client* client, const char c);
			void	unsetModes(const std::string& modes);
			void	unsetUserModes(Client* client, const std::string& modes);
			void	unsetMode(const char c);
			void	unsetUserMode(Client* client, const char c);
			void	inviteMember(Client* client);
	};
}

#endif
