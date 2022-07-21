/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:34:13 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 16:52:52 by minsunki         ###   ########seoul.kr  */
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

namespace ft::irc
{
	class Client; /*	TODO	*/

	class Server
	{
		friend class Client;
		
		private:
			
			std::vector<pollfd>							_pfds;
			std::queue<std::pair<int, std::string>>		_sque; // maybe create reply/msg class?
			std::map<int, Client*>						_clients;
			const int									_port;
			int											_lfd;

			void	accept();
			void	queue (const int& fd, std::string msg);
			void	flush();

		public:
			Server (std::string port);
			virtual	~Server();

			void	initialize();
			void	run();

	};
}

#endif