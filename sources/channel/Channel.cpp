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
		_prefix = '&';
		// std::cout << "channel creat name: " << name << " prefix: " << name[0] << std::endl;
		if (irc::isChPrefix(name[0]))
		{
			_name = name.substr(1);
			_prefix = name[0];
		}
		else
			_name = name;
		_modes.insert('n');
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

	void	Channel::sendNames(const Client* client) const
	{
		std::string	str = _server->getPrefix(client) + " ";
		str += (to_string(RPL_NAMREPLY) + " " + client->getNick());
		if (hasMode('p'))
			str += " * ";
		else if (hasMode('s'))
			str += " @ ";
		else
			str += " = ";
		str += getFName() + " :";

		std::string	ustr;
		clients_t::const_iterator	it = _clients.begin();

		for (size_t i = 0; i < getSize(); ++i)
		{
			Client*	cli = _server->getClient(*it);
			if (!cli)
				PE("Channel::sendNames tried to getClient a ghost");
			if ((i % 10) == 0)
			{
				if (i && ustr.size())
					client->queue(str + ustr);
				ustr = "";
			}
			// if (cli->hasMode('i')) // won't visibility flags
			if (ustr.size())
				ustr += " ";
			if (hasUserMode(cli, 'O') || hasUserMode(cli, 'o') || cli->hasMode('o'))
				ustr += "@";
			ustr += cli->getNick();
			it++;
		}
		
		if (ustr.size())
			client->queue(str + ustr);

		client->queue(_server->getPrefix(client) + " " + to_string(RPL_ENDOFNAMES)
					+ " " + client->getNick() + " " + getFName() + " :End of /NAMES list");
	}

	void	Channel::broadcast(const Client* client, const std::string msg) const
	{
		clients_t::iterator	it = _clients.begin();
		std::string			prefix = _server->getPrefix(client);

		while (it != _clients.end())
		{
			Client*	client = _server->getClient(*it);
			if (!client)
				PE("Channel had ghost client (Channel broadcast)");
			client->queue(prefix + " " + msg);	
			++it;
		}
	}

	bool	Channel::isInvited(const Client* client) const
	{
		return (_invites.count(client->getFD()));
	}

	bool	Channel::isMember(const Client* client) const
	{
		return (isMember(client->getFD()));
	}

	bool	Channel::isMember(const int fd) const
	{
		return (_clients.count(fd));
	}

	bool	Channel::hasMode(const char c) const 
	{
		return (_modes.count(c));
	}

	bool	Channel::hasUserMode(const Client* client, const char c) const
	{
		umodes_t::const_iterator	fit = _user_modes.find(client->getFD());
		if (fit != _user_modes.end())
			return (fit->second.find(c) != fit->second.end());
		// PE("Tried to call Channel::hasUserMode on ghost");
		return (false);
	}

	void	Channel::addClient(const Client* client)
	{
		_clients.insert(client->getFD());
		if (_invites.count(client->getFD()))
			_invites.erase(client->getFD());

		// const std::string	prefix = _server->getPrefix(client) + " ";
		// client->queue(prefix + to_string(RPL_NAMREPLY) + " " + client->getNick() + " = " + getFName() + " :" + getMembers());
		// client->queue(prefix + to_string(RPL_ENDOFNAMES) + " " + client->getNick() + " " + getFName() + " :End of /NAMES list");
	}

	void	Channel::rmClient(const Client* client)
	{
		if (!isMember(client))
			PE("Tried to Channel::rmClient on non-member client");
		_user_modes.erase(client->getFD());
		_clients.erase(client->getFD());
	}

	char	Channel::getPrefix() const
	{
		return (_prefix);
	}

	const std::string&	Channel::getName() const
	{
		return (_name);
	}

	const std::string	Channel::getFName() const
	{
		return (getPrefix() + getName());
	}

	const std::string&	Channel::getTopic() const
	{
		return (_topic);
	}

	const std::string&	Channel::getKey() const
	{
		return (_key);
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

	const Channel::modes_t&	Channel::getUserModes(Client* client)
	{
		return (_user_modes[client->getFD()]);
		// umodes_t::const_iterator	fit = _user_modes.find(client->getFD());
		// if (fit != _user_modes.end())
		// 	return (fit->second);
		// // PE("Tried to call Channel::getUserModes on ghost");
		// return (_user_modes.begin()->second);
	}

	std::string	Channel::getUserModestr(Client* client) const
	{
		std::string					ret;
		umodes_t::const_iterator	fit = _user_modes.find(client->getFD());

		if (fit == _user_modes.end())
			return (ret);
		modes_t::const_iterator		it = fit->second.begin();
		while (it != fit->second.end())
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

	const size_t&	Channel::getMaxClient() const
	{
		return (_max_client);
	}


	void	Channel::setMaxClient(size_t max)
	{
		_max_client = max;
	}

	void	Channel::setKey(const std::string& key)
	{
		_key = key;
	}

	void	Channel::setTopic(const std::string& topic)
	{
		_topic = topic;
	}

	bool	_isValid(const char c)
	{
		return (c == 'i' || c == 'o'); // all channel modes
	}

	void	Channel::setModes(const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			if (_isValid(*it))
				_modes.insert(*it);
			++it;
		}
	}

	void	Channel::setMode(const char c)
	{
		_modes.insert(c);
	}

	void	Channel::setUserModes(Client* client, const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			if (_isValid(*it))
				_user_modes[client->getFD()].insert(*it); // maybe check for faults?
			++it;
		} 
	}

	void	Channel::setUserMode(Client* client, const char c)
	{
		_user_modes[client->getFD()].insert(c);
	}

	void	Channel::unsetModes(const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			_modes.erase(*it);
			++it;
		}
	}

	void	Channel::unsetMode(const char c)
	{
		_modes.erase(c);
	}

	void	Channel::unsetUserModes(Client* client, const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			_user_modes[client->getFD()].erase(*it);
			++it;
		}
	}

	void	Channel::unsetUserMode(Client* client, const char c)
	{
		_user_modes[client->getFD()].erase(c);
	}

	void	Channel::inviteMember(Client* client)
	{
		_invites.insert(client->getFD());
	}

}
