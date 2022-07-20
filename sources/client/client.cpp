/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:58:48 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 01:55:22 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

#include <iostream>

#include <sys/socket.h>

namespace ft::irc
{
	Client::Client (const int& fd)
	:	_fd(fd)
	{}

	Client::~Client()
	{
		close(_fd);
	}

	void	Client::recv()
	{
		int		rs;
		char	buf[512];

		rs = ::recv(_fd, buf, 512, 0);
		buf[rs] = '\0'; /*	TODO:: proper CRLF detection, potential overflow rn	*/
		_buf += buf;

		std::cout << "client fd [" << _fd << "] recv, ";
		std::cout << "buffer content (" << _buf.size() << ")-----" << std::endl;
		std::cout << _buf << std::endl;
		std::cout << "----- end of buffer -----" << std::endl;
	}

	const int&	Client::getFD() const
	{
		return (_fd);
	}
}