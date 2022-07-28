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
	:	_server(server), _name(name), _topic("")
	{}

	Channel::~Channel()
	{
		// do something with _clients?
	}

	bool	Channel::isMember(const Client* client)
	{
		return (_clients.count(client->getFD()));
	}

	bool	Channel::hasMode(const char c)
	{
		return (_modes.count(c));
	}

	void	Channel::addClient(const Client* client)
	{
		_clients.insert(client->getFD());
		_server->queue(client->getFD(), _server->getPrefix(client) + " " + to_string(RPL_NAMREPLY)
										+ " " + client->getNick() + " = #" + getName() + " :" + getMembers());
		_server->queue(client->getFD(), _server->getPrefix(client) + " " + to_string(RPL_ENDOFNAMES)
										+ " " + client->getNick() + " #" + getName() + " :End of /NAMES list");
		_server->queue(client->getFD(), _server->getPrefix(client) + " JOIN #" + getName());
	}

	void	Channel::rmClient(const Client* client)
	{
		if (!isMember(client))
			PE("Tried to Channel::rmClient on non-member client");
		_clients.erase(client->getFD());
		_server->queue(client->getFD(), _server->getPrefix(client) + " PART #" + getName());
	}

	const std::string&	Channel::getName() const
	{
		return (_name);
	}

	const std::string&	Channel::getTopic() const
	{
		return (_topic);
	}

	const Channel::client_t&	Channel::getClients() const
	{
		return (_clients);
	}

	const Channel::mode_t&	Channel::getModes() const
	{
		return (_modes);
	}

	std::string	Channel::getModestr() const
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

	std::string	Channel::getMembers() const
	{
		std::string	ret;

		client_t::const_iterator	it = _clients.begin();
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
