/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:39:13 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 16:51:41 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "../util.hpp"
#include "../debug.hpp"
#include "../client/client.hpp"

#include <cstdlib>
#include <iostream>

#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

namespace ft::irc
{
	Server::Server(std::string port)
	:	_port(ft::stoi(port))
	{}

	Server::~Server()
	{
		close(_lfd); // check if this can somehow cause problems?
	}

	void	Server::initialize()
	{
		int			sock;
		sockaddr_in	sin;
		protoent	*pe;
		pollfd		pfd;

		pe = static_cast<protoent*>(DBGV(NULL, getprotobyname("tcp"), "getprotobyname"));
		sock = DBG(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
		fcntl(sock, F_SETFL, O_NONBLOCK);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(_port);
		DBG(-1, bind(sock, reinterpret_cast<sockaddr*>(&sin), sizeof(sin)), "bind");
		DBG(-1, listen(sock, 42), "listen");

		_lfd = sock;
		_pfds.push_back({_lfd, POLLIN, 0});
	}

	void	Server::queue(const int& fd, std::string msg)
	{
		_sque.push(std::make_pair(fd, msg));
	}

	void	Server::flush()
	{
		while (_sque.size())
		{
			int&			fd = _sque.front().first;
			std::string&	msg = _sque.front().second;

			/*	TODO make better send function	*/
			send(fd, &msg[0], msg.size(), 0);
			_sque.pop();
		}
	}

	void	Server::accept()
	{
		int	sock;

		sock = -1;
		while ((sock = ::accept(_lfd, NULL, NULL)) != -1)
		{
			std::cout << "new connection accepted" << std::endl;

			_pfds.push_back({sock, POLLIN, 0});
			if (!(_clients.insert(std::make_pair(sock, new Client(sock, this))).second))
				PE("failed inserting client to _clients.");

			std::cout << "current client #:" << _clients.size() << std::endl;
		}

		if (errno != EWOULDBLOCK)
			DBG_OFS((69 - 61), "accept");
	}

	void	Server::run()
	{
		int	pr;

		while (1)
		{
			_pfds.reserve(42);
			pr = poll(&_pfds[0], _pfds.size(), 100), DBG(-1, pr, "poll");

			if (pr)
			{
				int	size = _pfds.size();			

				if (_pfds[0].revents)
					this->accept();

				for (int i = 1; i < size; ++i)
				{
					pollfd& pfd = _pfds[i];

					if (!pfd.revents)
						continue;
					if (!(pfd.revents & POLLIN))
						PE("poll revent is set wrong");

					_clients[pfd.fd]->recv();
				}
			}
			
			if (_sque.size())
				this->flush();
		}
	}
}