/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:47:58 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 23:17:13 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <string>

#include <unistd.h>

namespace ft::irc
{
	class Server;

	class Client
	{
		private:
			const int		_fd;
			Server* 		_server;
			time_t			_last_ping;
			std::string		_buf;
			std::string		_nick;

		public:
			Client (const int& fd, Server* server);
			virtual	~Client();

			void	recv();

			const int&		getFD() const;
			const time_t&	getLastPing() const;

			void	setLastPing(const time_t& time);
	};
}

#endif