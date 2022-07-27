/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:58:48 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/27 16:23:57 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Command.hpp"
#include "server/Server.hpp"
#include "debug.hpp"

#include <iostream>
#include <ctime>

#include <sys/socket.h>

namespace irc
{
	int	Client::parse()
	{
		// std::cout << "client::parse" << std::endl;
		int		ret = 0;
		size_t	cur = 0;
		size_t	fpos;
		
		while ((fpos = _buf.find('\r', cur)) != std::string::npos)
		{
			++ret;
			// _parse(_buf.substr(cur, fpos - cur));
			// std::cout << _buf.substr(cur, fpos - cur) << std::endl;
			Command	cmd(this, _server, _buf.substr(cur, fpos - cur));
			cmd.run();
			cur = fpos + 2;
		}

		_buf.erase(0, _buf.find_last_of('\n') + 2); // why + 2?
		
		// std::cout << "buffer after parse" << std::endl;
		// std::cout << _buf << std::endl;
		// std::cout << "EOB" << std::endl;
		return (ret);
	}
}

namespace irc
{
	Client::Client (const int& fd, Server* server)
	:	_fd(fd), _server(server), _cchannel(NULL), _last_ping(std::time(0))
	{}

	Client::~Client()
	{
		close(_fd);
	}

	void	Client::recv()
	{
		int		rs;
		char	buf[512 + 1];

		rs = ::recv(_fd, buf, 512, 0), DBG(-1, rs, "recv");
		// no need to check EWOULDBLOCK since we polled
		// buffer size is 512 per rfc.
		
		if (rs == 0)
		{
			// check if quit was received, if not, generate appropriate quit message
			_server->rmclient(this);
			return ;
		}

		buf[rs] = '\0'; /*	TODO:: read buffer and parse command	*/
		_buf += buf;

		// if (_buf.find("\r\n")) // end of a cmd, parse
		this->parse();

		// std::cout << "client fd [" << _fd << "] recv, ";
		// std::cout << "buffer content (" << _buf.size() << ")-----" << std::endl;
		// std::cout << _buf << std::endl;
		// std::cout << "----- end of buffer -----" << std::endl;
		// _server->queue(_fd, "001");
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

	const std::string&	Client::getNick() const
	{
		return (_nick);
	}

	const std::string&	Client::getUserName() const
	{
		return (_user_name);
	}

	const std::string&	Client::getRealName() const
	{
		return (_real_name);
	}

	const Client::mode_t&	Client::getModes() const
	{
		return (_modes);
	}

	const Channel*	Client::getCChannel() const
	{
		return (_cchannel);
	}

	bool	Client::hasMode(char c) const
	{
		return (_modes.count(c));
	}

	void	Client::setLastPing(const time_t& time)
	{
		_last_ping = time;
	}
	// void	Client::_parse(std::string str)
	// {
	
	// }

	void	Client::setNick(const std::string& str)
	{
		_last_nick = _nick;
		_nick = str;
	}

	void	Client::setUserName(const std::string& name)
	{
		_user_name = name;
	}

	void	Client::setRealName(const std::string& name)
	{
		_real_name = name;
	}

	void	Client::setModes(const std::string& modes)
	{
		std::string::const_iterator it = modes.begin();
		while (it != modes.end())
		{
			_modes.insert(*it);
			it++;
		}
	}

	void	Client::unsetModes(const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			_modes.erase(*it);
			it++;
		}
	}

	void	Client::setCChannel(Channel* channel)
	{
		_cchannel = channel;
	}
}