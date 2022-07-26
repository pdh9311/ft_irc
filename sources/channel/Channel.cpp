/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:20:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/26 15:42:10 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "channel/Channel.hpp"
#include "client/Client.hpp"
#include "debug.hpp"

namespace irc
{

}

namespace irc
{
	Channel::Channel(const std::string name)
	:	_name(name)
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
	}

	void	Channel::rmClient(const Client* client)
	{
		if (!isMember(client))
			PE("Tried to Channel::rmClient on non-member client");
		_clients.erase(client->getFD());
	}

	const std::string&	Channel::getName() const
	{
		return (_name);
	}

	const Channel::client_t&	Channel::getClients() const
	{
		return (_clients);
	}

	const Channel::mode_t&	Channel::getModes() const
	{
		return (_modes);
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

	void	Channel::unsetModes(const std::string& modes)
	{
		std::string::const_iterator	it = modes.begin();
		while (it != modes.end())
		{
			_modes.erase(*it);
			it++;
		}
	}

}