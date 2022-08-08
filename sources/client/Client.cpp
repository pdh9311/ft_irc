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
			std::cout << "<< [" + _buf.substr(cur, fpos - cur) << "]" << std::endl;
			Command	cmd(this, _server, _buf.substr(cur, fpos - cur));
			cmd.run();
			_buf = _buf.substr(fpos + 2);
			cur = 0;
		}

		return (ret);
	}
}

namespace irc
{
	Client::Client (const int& fd, Server* server)
	:	_fd(fd), _server(server), _on_channel(false),
		_last_ping(std::time(0)), _status(PENDING), _welcome(false)
	{
		if (!server->getPass().size())	// 서버의 비밀번호가 없는 경우에도 사용할 수 있도록 하기 위함.
			_status = AUTH;
	}

	Client::~Client()
	{
		close(_fd);
	}

	void	Client::recv()
	{
		int		rs;
		char	buf[512 + 1];

		rs = ::recv(_fd, buf, 512, 0), DBG(-1, rs, "recv");
		if (rs == 0)
		{
			// check if quit was received, if not, generate appropriate quit message
			_server->rmClient(this);
			return ;
		}

		buf[rs] = '\0';
		_buf += buf;

		this->parse();
	}

	void	Client::queue(std::string msg) const
	{
		_server->queue(_fd, msg);
	}

	char	Client::getStatus() const
	{
		return (_status);
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

	const std::string	Client::getModestr() const
	{
		std::string				ret;
		mode_t::const_iterator	it = _modes.begin();

		while (it != _modes.end())
		{
			ret += *it;
			++it;
		}
		return (ret);
	}

	// const Channel*	Client::getCChannel() const
	// {
	// 	return (_cchannel);
	// }

	bool	Client::isOnChannel() const
	{
		return (_on_channel);
	}

	bool	Client::getWelcome() const
	{
		return (_welcome);
	}

	bool	Client::hasMode(char c) const
	{
		return (_modes.count(c));
	}

	bool	Client::isLoggedIn() const
	{
		return (_status == LOGGEDIN);
	}

	const std::string&	Client::getAwayMsg() const
	{
		return (_away_msg);
	}

	void	Client::setAwayMsg(const std::string& msg)
	{
		_away_msg = msg;
	}

	void	Client::setLastPing(const time_t& time)
	{
		_last_ping = time;
	}

	void	Client::setNick(const std::string& str)
	{
		_last_nick = _nick;
		_nick = str;
	}

	void	Client::setUserName(const std::string& name)
	{
		_user_name = name;
	}

	void	Client::setHostName(const std::string& name)
	{
		_host_name = name;
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

	void	Client::setMode(const char c)
	{
		_modes.insert(c);
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

	void	Client::unsetMode(const char c)
	{
		_modes.erase(c);
	}

	// void	Client::setCChannel(Channel* channel)
	// {
	// 	_cchannel = channel;
	// }

	void	Client::setOnChannel(bool b)
	{
		_on_channel = b;
	}

	void	Client::setStatus(const char status)
	{
		_status = status;
	}

	void	Client::setWelcome(bool i)
	{
		_welcome = i;
	}


	const std::string&	Client::getPastName() const
	{
		return _past_name;
	}
	void	Client::setPastName(const std::string& name)
	{
		_past_name = name;
	}

	const std::string&	Client::getHostName() const
	{
		return (_host_name);
	}

}
