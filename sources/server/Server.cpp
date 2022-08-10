#include "Server.hpp"
#include "util.hpp"
#include "debug.hpp"
#include "client/Client.hpp"
#include "channel/Channel.hpp"

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cerrno>

#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

// private funcs
namespace irc
{

	void	Server::accept()
	{
		int	sock;

		sock = -1;
		while ((sock = ::accept(_lfd, NULL, NULL)) != -1)
		{
			Client*	client = new Client(sock, this);
			pollfd	pfd;

			pfd.fd = sock;
			pfd.events = POLLIN;
			pfd.revents = 0;

			_pfds.push_back(pfd);
			if (!(_clients.insert(std::make_pair(sock, client)).second))
				PE("failed inserting client to _clients.");

			if (_pass.empty())
				client->setStatus(Client::AUTH);
		}

		if (errno != EWOULDBLOCK)
			DBG_OFS((44 - 26), "accept");
	}

	void	Server::ping()
	{
		time_t				ct = std::time(0);
		clients_t::iterator	it = _clients.begin();

		while (it != _clients.end())
		{
			Client*&	client = it->second;

			if (ct - client->getLastPing() >= conf.get_Y().getPingFrequency() * 4)	// give 3 times to try
				rmClient(client);
			else if (client->getStatus() >= Client::LOGGEDIN)
				this->queue(client->getFD(), "PING " + client->getNick());
			it++;
		}
	}
}

// public funcs
namespace irc
{
	Server::Server(const std::string port, const std::string pass)
	:	_port(irc::stoi(port)), _pass(pass)
	{}

	Server::~Server() // do we need graceful exit?
	{
		while (!_channels.empty())
		{
			delete _channels.begin()->second;
			_channels.erase(_channels.begin());
		}

		while (!_clients.empty())
		{
			delete _clients.begin()->second;
			_clients.erase(_clients.begin());
		}

		close(_lfd);
	}

	// void	Server::welcome (Client* client)
	// {

	// }

	void	Server::queue (const Client* client, std::string msg)
	{
		queue(client->getFD(), msg);
	}

	void	Server::queue (const int& fd, std::string msg)
	{
		std::cout << ">> [" << msg << "]" << std::endl;
		_sque.push(std::make_pair(fd, msg + "\r\n"));
	}

	void	Server::initialize()
	{
		int			sock;
		int option = 1;	// SO_REUSEADDR 의 옵션 값을 TRUE
		sockaddr_in	sin;
		protoent	*pe;
		pollfd		pfd;

		pe = static_cast<protoent*>(DBGV(NULL, getprotobyname("tcp"), "getprotobyname"));
		sock = DBG(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
		DBG(-1, setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)), "setsockopt");	// SO_REUSEADDR을 지정해 주면 같은 포트에 대해 다른 소켓이 bind()되는 것을 허락해 주기 때문에 bind()에러 없이 프로그램을 실행할 수 있다.
		fcntl(sock, F_SETFL, O_NONBLOCK);
		std::memset(&sin, 0, sizeof(sin));	// 구조체 초기화 필요함.(sockaddr과 sockaddr_in 크기를 맞추기 위해서 sockaddr_in에 zero 배열이 있는데 이 배열을 0으로 만들어줘야 하기때문에 값을 대입하기 전에 0으로 초기화기 필요함.)
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(_port);
		DBG(-1, bind(sock, reinterpret_cast<sockaddr*>(&sin), sizeof(sin)), "bind");
		DBG(-1, listen(sock, 42), "listen");

		_lfd = sock;
		pfd.fd = _lfd;
		pfd.events = POLLIN;
		pfd.revents = 0;
		_pfds.push_back(pfd);
	}

	void	Server::flush()
	{
		while (_sque.size())
		{
			int&			fd = _sque.front().first;
			std::string&	msg = _sque.front().second;

			send(fd, &msg[0], msg.size(), 0);
			_sque.pop();
		}

		while (_dque.size())
		{
			int	fd = *(_dque.begin());

			// channels_t::iterator	chit = _channels.begin();
			// while (chit != _channels.end())
			// {
			// 	channels_t::iterator	tmp = chit++;
			// 	Channel*	channel = tmp->second;

			// 	if (channel->isMember(fd) && channel->getSize() == 1)
			// 		delete tmp->second;
			// 	_channels.erase(tmp);
			// }

			pfds_t::iterator it = _pfds.begin();
			while (++it != _pfds.end())
				if (it->fd == fd)
					break ;
			if (it == _pfds.end())
				PE("something went terribly wrong with pfds");
			_pfds.erase(it);

			clients_t::iterator cit = _clients.find(fd);
			if (cit == _clients.end())
				PE("something went terribly wrong with clients");
			delete cit->second;
			_clients.erase(cit);
			_dque.erase(_dque.begin());
		}
	}

	void	Server::run()
	{
		const int	ptime = conf.get_Y().getPingFrequency();
		time_t		last_ping = 0;
		int			pr;

		std::cout << "irc server started. Port: [" << _port << "] passwd: [" << _pass << "]" << std::endl;

		while (1)
		{
			if (std::time(0) - last_ping > ptime)
				this->ping(), last_ping = std::time(0);

			_pfds.reserve(42);
			pr = poll(&_pfds[0], _pfds.size(), 1000), DBG(-1, pr, "poll");

			if (_pfds[0].revents)
				this->accept();

			if (pr)
			{
				size_t	size = _pfds.size();

				for (size_t i = 1; i < size; ++i)
				{
					pollfd& pfd = _pfds[i];

					if (!pfd.revents)
						continue;
					if (!(pfd.revents & POLLIN))
						PE("poll revent is set wrong");
					if (_clients.count(pfd.fd))
						_clients[pfd.fd]->recv();
					else
						PE("tried to recv on non-existant client")
				}
			}

			// destroy empty channels.
			channels_t::iterator	it = _channels.begin();
			while (it != _channels.end())
			{
				channels_t::iterator tmp = it++;
				if (!tmp->second->getSize())
				{
					delete tmp->second;
					_channels.erase(tmp);
				}
			}

			if (_sque.size() || _dque.size())
				this->flush();
		}
	}

	void	Server::rmClient(Client* client)
	{
		channels_t::const_iterator	it = _channels.begin();

		while (it != _channels.end())
		{
			Channel*	chan = it->second;
			if (chan->isMember(client))
			{
				chan->broadcast(client, "QUIT :connection lost");
				chan->rmClient(client);
			}
			++it;
		}
		_dque.insert(client->getFD());
	}

	void	Server::rmChannel(Channel* channel)
	{
		channels_t::iterator	fit = _channels.find(channel->getName());
		if (fit == _channels.end())
			PE("Tried to rmChannel that doesn't exist!");
		delete fit->second;
		_channels.erase(fit);
	}

	Channel*	Server::addChannel(std::string name)
	{
		Channel*	channel = new Channel(this, name);
		if (isChPrefix(name[0]))
			name = name.substr(1);
		_channels.insert(std::make_pair(name, channel));
		return (channel);
	}

	const Server::clients_t&	Server::getClients() const
	{
		return (_clients);
	}

	Client*	Server::getClient(int fd) const
	{
		clients_t::const_iterator	fit = _clients.find(fd);
		if (fit != _clients.end())
			return (fit->second);
		return (NULL);
	}

	Client*	Server::getClient(const std::string& name) const
	{
		clients_t::const_iterator	it = _clients.begin();
		while (it != _clients.end())
		{
			if (it->second->getNick() == name)
				return (it->second);
			++it;
		}
		return (NULL);
	}

	const Server::channels_t&	Server::getChannels() const
	{
		return (_channels);
	}

	Channel*	Server::getChannel(std::string name) const
	{
		if (isChPrefix(name[0]))
			name = name.substr(1);
		if (hasChannel(name))
			return (_channels.find(name)->second);
		return (NULL);
	}

	bool	Server::hasChannel(std::string name) const
	{
		if (isChPrefix(name[0]))
			name = name.substr(1);
		return (_channels.count(name));
	}

	const std::string	Server::getName() const
	{
		return ("localhost");//(conf.get_B().getServerName());
	}

	const std::string	Server::getPrefix(const Client* client) const
	{
		std::string	ret = ":";
		ret += client->getNick();
		ret += "!";
		ret += client->getUserName();
		ret += "@";
		ret += getName();
		return (ret);
	}

	const std::string	Server::getPass() const
	{
		return _pass;
	}

	Server::channels_t	Server::getClientChannels(Client* client)
	{
		Server::channels_t				client_channels;
		Server::channels_t::iterator	it = _channels.begin();
		while (it != _channels.end())
		{
			Channel*	channel = it->second;
			irc::Channel::clients_t	chcl = channel->getClients();
			irc::Channel::clients_t::iterator	chclit = chcl.find(client->getFD());
			if (chclit != chcl.end())
				client_channels.insert(std::pair<std::string, Channel*>(channel->getName(), channel));
			++it;
		}
		return (client_channels);
	}
}
