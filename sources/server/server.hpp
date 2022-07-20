/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:34:13 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 01:11:59 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <vector>
#include <string>
#include <utility>
#include <map>

#include <poll.h>

namespace ft::irc
{
	class Client; /*	TODO	*/

	class Server
	{
		private:
			std::vector<pollfd>							_pfds;
			std::vector<std::pair<int, std::string>>	_sque;
			std::map<int, Client*>						_clients;
			const int									_port;
			int											_lfd;

			void	accept();

		public:
			Server (std::string port);
			virtual	~Server();

			void	initialize();
			void	run();

	};
}

#endif