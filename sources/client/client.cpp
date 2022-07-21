/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:58:48 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/22 01:06:04 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "../server/server.hpp"

#include <iostream>
#include <ctime>

#include <sys/socket.h>

namespace ft::irc
{
	Client::Client (const int& fd, Server* server)
	:	_fd(fd), _server(server), _last_ping(std::time(0))
	{}

	Client::~Client()
	{
		close(_fd);
	}

	void	Client::recv()
	{
		int		rs;
		char	buf[512 + 1];

		rs = ::recv(_fd, buf, 512, 0); // buffer size is 512 per rfc.
		if (rs == 0)	/* TODO:: socket is closed. kill client?	*/
			void ;
		buf[rs] = '\0'; /*	TODO:: read buffer and parse command	*/
		_buf += buf;

		std::cout << "client fd [" << _fd << "] recv, ";
		std::cout << "buffer content (" << _buf.size() << ")-----" << std::endl;
		std::cout << _buf << std::endl;
		std::cout << "----- end of buffer -----" << std::endl;
		_server->queue(_fd, "001");
		// _server->queue(_fd, "hello client");
	}

	const int&	Client::getFD() const
	{
		return (_fd);
	}

	const time_t&	Client::getLastPing() const
	{
		return (_last_ping);
	}

	void	Client::setLastPing(const time_t& time)
	{
		_last_ping = time;
	}
}