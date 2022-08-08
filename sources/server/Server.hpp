#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "server/Config.hpp"

#include <vector>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <map>

#include <poll.h>

namespace irc
{
	class Client;
	class Channel;
	class Config;

	class Server
	{
		friend class Client;

		public:
			typedef std::vector<pollfd>							pfds_t;
			typedef std::queue<std::pair<int, std::string> >	sque_t;
			typedef std::set<int>								dque_t;
			typedef	std::map<int, Client*>						clients_t;
			typedef std::map<std::string, Channel*>				channels_t;
			Config												conf;

		private:
			const int			_port;
			const std::string	_pass;
			pfds_t				_pfds;
			sque_t				_sque; // maybe create reply/msg class?
			dque_t				_dque;
			clients_t			_clients;
			channels_t			_channels;
			int					_lfd;

			void	accept();
			void	flush();
			void	ping();

		public:
			Server (const std::string port, const std::string pass);
			virtual	~Server();

			// void		welcome (Client* client);
			void		queue (const Client* client, std::string msg);
			void		queue (const int& fd, std::string msg);
			void		initialize();
			void		run();
			void		rmClient(Client* client);
			void		rmChannel(Channel* channel);
			Channel*	addChannel(std::string name);

			const clients_t&	getClients() const;
			Client*				getClient(int fd) const;
			Client*				getClient(const std::string& name) const;
			const channels_t&	getChannels() const;
			Channel*			getChannel (std::string name) const;
			bool				hasChannel (std::string name) const;
			const std::string	getName() const;
			const std::string	getPrefix (const Client* client) const;
			const std::string	getPass() const;

			channels_t	getClientChannels(Client* client);
	};
}

#endif
