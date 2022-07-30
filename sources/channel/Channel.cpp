#include "channel/Channel.hpp"
#include "server/Server.hpp"
#include "client/Client.hpp"
#include "client/numerics.hpp"
#include "debug.hpp"
#include "util.hpp"

#include <iostream>

namespace irc
{

}

namespace irc
{
	Channel::Channel(Server* server, const std::string name)
	:	_server(server)
	{
		_is_local = true;
		if (name[0] == '#' || name[0] == '&')
		{
			_name = name.substr(1);
			_is_local = (name[0] == '#');
		}
		else
			_name = name;
	}

	Channel::~Channel()
	{
		clients_t::iterator	it = _clients.begin();
		
		while (it != _clients.end())
		{
			Client*	cli = _server->getClient(*it);
			if (!cli)
				PE("Channel had ghost client (Channel destructor)");
			_server->queue(*it, "PART " + getFName());
			++it;
		}
	}

	bool	Channel::isMember(const Client* client)
	{
		return (isMember(client->getFD()));
	}

	bool	Channel::isMember(const int fd)
	{
		return (_clients.count(fd));
	}

	bool	Channel::hasMode(const char c)
	{
		return (_modes.count(c));
	}

	void	Channel::addClient(const Client* client)
	{
		_clients.insert(client->getFD());

		const std::string	prefix = _server->getPrefix(client) + " ";
		client->queue(prefix + to_string(RPL_NAMREPLY) + " " + client->getNick() + " = " + getFName() + " :" + getMembers());
		client->queue(prefix + to_string(RPL_ENDOFNAMES) + " " + client->getNick() + " " + getFName() + " :End of /NAMES list");
		client->queue(prefix + "JOIN " + getFName());
	}

	void	Channel::rmClient(const Client* client)
	{
		if (!isMember(client))
			PE("Tried to Channel::rmClient on non-member client");
		_clients.erase(client->getFD());
		client->queue(_server->getPrefix(client) + " PART " + getFName());
	}

	const std::string&	Channel::getName() const
	{
		return (_name);
	}

	const std::string	Channel::getFName() const
	{
		return (_is_local ? "#" : "&") + getName();
	}

	const std::string&	Channel::getTopic() const
	{
		return (_topic);
	}

	const Channel::clients_t&	Channel::getClients() const
	{
		return (_clients);
	}

	const Channel::modes_t&	Channel::getModes() const
	{
		return (_modes);
	}

	std::string	Channel::getModestr() const
	{
		std::string				ret;
		modes_t::const_iterator	it = _modes.begin();

		while (it != _modes.end())
		{
			ret += *it;
			++it;
		}
		return (ret);
	}

	std::string	Channel::getMembers() const
	{
		std::string	ret;

		clients_t::const_iterator	it = _clients.begin();
		while (it != _clients.end())
		{
			const Client*	client = _server->getClient(*it);
			if (!client)
				PE("Channel is holding invalid fd");
			ret += "@" + client->getNick() + " "; // TODO:: @ +
			++it;
		}
		return (ret);
	}

	size_t	Channel::getSize() const
	{
		return (_clients.size());
	}

	void	Channel::setTopic(const std::string& topic)
	{
		_topic = topic;
	}

	void	Channel::setModes(const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			_modes.insert(*it);
			it++;
		}
	}

	void	Channel::setMode(const char c)
	{
		_modes.insert(c);
	}

	void	Channel::unsetModes(const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			_modes.erase(*it);
			it++;
		}
	}

	void	Channel::unsetMode(const char c)
	{
		_modes.erase(c);
	}

	void	Channel::inviteMember(Client* client)
	{
		_invites.insert(client->getFD());
	}

}
