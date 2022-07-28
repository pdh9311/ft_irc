#include "Server.hpp"
#include "util.hpp"
#include "debug.hpp"
#include "client/Client.hpp"
#include "channel/Channel.hpp"

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
			std::cout << "new connection accepted" << std::endl;

			pollfd	pfd;
			pfd.fd = sock;
			pfd.events = POLLIN;
			pfd.revents = 0;

			_pfds.push_back(pfd);
			if (!(_clients.insert(std::make_pair(sock, new Client(sock, this))).second))
				PE("failed inserting client to _clients.");

			std::cout << "current client #:" << _clients.size() << std::endl;
		}

		if (errno != EWOULDBLOCK)
			DBG_OFS((69 - 61), "accept");
	}

	void	Server::ping()
	{
		time_t								ct = std::time(0);
		std::map<int, Client*>::iterator	it = _clients.begin();

		while (it != _clients.end())
		{
			Client*&	client = it->second;

			if (ct - client->getLastPing() >= 5)	/*	TODO:: make proper config class	*/
				(void)client; // client is not responding to ping. kill?

			this->queue(client->getFD(), "PING minsunki");	/*	TODO:: replace placeholder with something fitting	*/
			it++;
		}
	}

	Channel*	Server::createChannel(const std::string& name)
	{
		Channel*	channel = new Channel(this, name);
		_channels.insert(std::make_pair(name, channel));
		return (channel);
	}
}

// public funcs
namespace irc
{
	Server::Server(std::string port)
	:	_port(irc::stoi(port))
	{}

	Server::~Server()
	{
		close(_lfd); // check if this can somehow cause problems?
	}

	// void	Server::welcome (Client* client)
	// {
	// 	// queue(getPrefix(client) + "001" )
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

			/*	TODO make better send function	*/
			send(fd, &msg[0], msg.size(), 0);
			_sque.pop();
		}

		while (_dque.size())
		{
			int	fd = *(_dque.begin());
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
		time_t	last_ping = 0;
		int		pr;

		while (1)
		{
			if (std::time(0) - last_ping > 60)	/*	TODO:: proper config class	*/
				this->ping(), last_ping = std::time(0);

			_pfds.reserve(42);
			pr = poll(&_pfds[0], _pfds.size(), 1000), DBG(-1, pr, "poll");


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

					if (_clients.count(pfd.fd))
						_clients[pfd.fd]->recv();
					else
						PE("tried to recv on non-existant client")
				}
			}

			if (_sque.size() || _dque.size())
				this->flush();

			// destroy empty channels.
			channels_t::iterator	it = _channels.begin();
			while (it != _channels.end())
			{
				channels_t::iterator tmp = it++;

				if (tmp->second->getClients().empty())
				{
					delete tmp->second;
					_channels.erase(tmp);
				}
			}
		}
	}

	void	Server::rmclient(Client* client)
	{
		// queue clients to be removed since vector.erase will ruin iterators
		// if we need to send something to client before termination, this is a good time to do so
		_dque.insert(client->getFD());
		// delete queue will be flushed after sque
	}

	void	Server::rmchannel(Channel* channel)
	{
		channels_t::iterator	fit = _channels.find(channel->getName());
		if (fit == _channels.end())
			PE("Tried to rmchannel that doesn't exist!");
		delete fit->second;
		_channels.erase(fit);
	}

	const Server::clients_t&	Server::getClients() const
	{
		return (_clients);
	}

	const Client*	Server::getClient(int fd) const
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

	Channel*	Server::getChannel(const std::string& name)
	{
		if (hasChannel(name))
			return (_channels[name]);
		return (createChannel(name));
	}

	bool	Server::hasChannel(const std::string& name) const
	{
		return (_channels.count(name));
	}

	const std::string	Server::getName() const
	{
		return ("localhost");
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
}
