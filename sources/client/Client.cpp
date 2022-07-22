/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:58:48 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:55 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Command.hpp"
#include "../server/Server.hpp"

#include <iostream>
#include <ctime>

#include <sys/socket.h>

namespace irc
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
		// if (rs == 0)	/* TODO:: socket is closed. kill client?	*/
			// void ;
		buf[rs] = '\0'; /*	TODO:: read buffer and parse command	*/
		_buf += buf;

		// if (_buf.find("\r\n")) // end of a cmd, parse
		this->parse();

		// std::cout << "client fd [" << _fd << "] recv, ";
		// std::cout << "buffer content (" << _buf.size() << ")-----" << std::endl;
		// std::cout << _buf << std::endl;
		// std::cout << "----- end of buffer -----" << std::endl;
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

	// void	Client::setLastPing(const time_t& time)
	// {
	// 	_last_ping = time;
	// }
	void	Client::_parse(std::string str)
	{
		// std::cout << "_parse called for [" << str << "]" << std::endl;
		size_t						cur = 0;
		size_t						fpos;
		std::string					prefix;
		std::string					cmd;
		// std::string					arg;
		std::vector<std::string>	args;

		if (str[cur] == ':') // has prefix
		{
			fpos = str.find(' ', ++cur);
			prefix = str.substr(cur, fpos - cur);
			cur = fpos;
		} // is message with only prefix valid? 

		while (str[cur] == ' ') cur++;

		fpos = str.find(' ', cur);
		cmd = str.substr(cur, fpos - cur);
		cur = fpos;

		while (cur != std::string::npos)
		{
			while (str[cur] == ' ') cur++;
			if (str[cur] == ':')
				fpos = std::string::npos;
			else
				fpos = str.find(' ', cur);
			// arg = str.substr(cur, fpos - cur);
			args.push_back(str.substr(cur, fpos - cur));
			cur = fpos;
		}

		// std::cout << "prefix: " << prefix << "#" << std::endl;
		// std::cout << "cmd: " << cmd << "#" <<  std::endl;
		// for(int i = 0; i < args.size(); ++i)
		// {
		// 	std::cout << "arg#" << i << ": " << args[i] << "#" <<  std::endl;
		// }

		// _cmds.push_back(Command(prefix, cmd, args));

	}

	int	Client::parse()
	{
		int		ret = 0;
		size_t	cur = 0;
		size_t	fpos;
		
		while ((fpos = _buf.find('\r', cur)) != std::string::npos)
		{
			++ret;
			_parse(_buf.substr(cur, fpos - cur));
			cur = fpos + 2;
		}

		_buf.erase(0, _buf.find_last_of('\n') + 2); // why + 2?
		
		// std::cout << "buffer after parse" << std::endl;
		// std::cout << _buf << std::endl;
		// std::cout << "EOB" << std::endl;
		return (ret);
	}
}