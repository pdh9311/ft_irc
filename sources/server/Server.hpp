/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:34:13 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/27 16:25:29 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

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

	class Server
	{
		friend class Client;
		public:
			typedef std::vector<pollfd>							pfds_t;
			typedef std::queue<std::pair<int, std::string> >	sque_t;
			typedef std::set<int>								dque_t;
			typedef	std::map<int, Client*>						clients_t;
			typedef std::map<std::string, Channel*>				channels_t;
			
		private:
			pfds_t		_pfds;
			sque_t		_sque; // maybe create reply/msg class?
			dque_t		_dque;
			clients_t	_clients;
			channels_t	_channels;
			const int	_port;
			int			_lfd;

			void	accept();
			void	flush();
			void	ping();
			Channel*	createChannel(const std::string& name);

		public:
			Server (std::string port);
			virtual	~Server();

			// void		welcome (Client* client);
			void		queue (const int& fd, std::string msg);
			void		initialize();
			void		run();
			void		rmclient(Client* client);
			void		rmchannel(Channel* channel);
			
			const clients_t&	getClients() const;
			const Client*		getClient(int fd) const;
			const channels_t&	getChannels() const;
			Channel*			getChannel (const std::string& name);
			bool				hasChannel (const std::string& name) const;
			const std::string	getName() const;
			const std::string	getPrefix (const Client* client) const;
	};
}

#endif