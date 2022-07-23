/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:34:13 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/24 00:39:27 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <map>

#include <poll.h>

namespace irc
{
	class Client; /*	TODO	*/
	class Channel; /*	TODO	*/

	class Server
	{
		friend class Client;
		
		private:
			
			std::vector<pollfd>							_pfds;
			std::queue<std::pair<int, std::string> >	_sque; // maybe create reply/msg class?
			std::map<int, Client*>						_clients;
			std::map<std::string, Channel*>				_channels;
			const int									_port;
			int											_lfd;

			void	accept();
			void	flush();
			void	ping();

		public:
			Server (std::string port);
			virtual	~Server();

			void	queue (const int& fd, std::string msg);
			void	initialize();
			void	run();

	};
}

#endif