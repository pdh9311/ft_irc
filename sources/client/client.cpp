/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:58:48 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 16:48:36 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "../server/server.hpp"

#include <iostream>

#include <sys/socket.h>

namespace ft::irc
{
	Client::Client (const int& fd, Server* server)
	:	_fd(fd), _server(server)
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
		buf[rs] = '\0'; /*	TODO:: read buffer and parse command	*/
		_buf += buf;

		std::cout << "client fd [" << _fd << "] recv, ";
		std::cout << "buffer content (" << _buf.size() << ")-----" << std::endl;
		std::cout << _buf << std::endl;
		std::cout << "----- end of buffer -----" << std::endl;

		_server->queue(_fd, "hello client");
	}

	const int&	Client::getFD() const
	{
		return (_fd);
	}
}