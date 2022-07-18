/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:29:19 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/18 16:36:36 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "util.hpp"
#include "debug.hpp"
#include <cstdlib>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/fcntl.h>

namespace ft
{
	irc::irc(std::string port)
	:	_port(ft::stoi(port))
	{}

	irc::~irc() 
	{

	}

	void	irc::initialize()
	{
		int					s;
		struct sockaddr_in	sin;
		struct protoent		*pe;
		struct pollfd		pfd;

		pe = (struct protoent*)XV(NULL, getprotobyname("tcp"), "getprotobyname");
		s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
		fcntl(s, F_SETFL, O_NONBLOCK);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(_port);
		X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind");
		X(-1, listen(s, 42), "listen");
		pfd.events = POLLIN;
		pfd.revents = 0;
		pfd.fd = s;

		_lfd = s;
		_pfds.push_back(pfd);
	}

	void	irc::accept()
	{
		int	new_sd;
		do
		{
			new_sd = ::accept(_lfd, NULL, NULL);
			std::cout << "new connection accepted" << std::endl;
			std::cout << "current fds: " << _pfds.size() << std::endl;

			if (new_sd < 0)
			{
				if (errno != EWOULDBLOCK)
				{
					std::cerr << "something went wrong with accept" << std::endl;
					exit(1);
				}
				break ;
			}
			struct pollfd	pfd;
			pfd.events = POLLIN;
			pfd.revents = 0;
			pfd.fd = new_sd;
			_pfds.push_back(pfd);

		} while (new_sd != -1);
	}

	void	irc::read(struct pollfd& pfd)
	{
		int&	fd = pfd.fd;

		int	r;
		char	buff[512];
		r = recv(fd, buff, 512, 0);
		buff[r] = 0;
		std::cout << buff << std::endl;
		
	}

	void	irc::loop()
	{
		int	pr;

		while(1)
		{
			_pfds.reserve(42);
			pr = poll(&_pfds[0], _pfds.size(), 1000), X(-1, pr, "poll");
		
			std::cout << pr << std::endl;
			if (pr == 0)
				continue ;
			
			int	vsize = _pfds.size();
			for (int i = 0; i < vsize; ++i)
			{
				struct pollfd&	pfd = _pfds[i];
				if (!pfd.revents)
					continue ;
				std::cout << "fd: " << pfd.fd << ", " << _lfd << std::endl;
				if (pfd.fd == _lfd)
					this->accept();
				else
					this->read(pfd);
				// else
				// 	this->aio();
			}

		}
	}

	
}