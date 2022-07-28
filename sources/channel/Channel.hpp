/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:08:35 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/28 12:57:14 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <set>
#include <string>

namespace irc
{
	class Server;
	class Client;

	class Channel
	{
		public:
			typedef std::set<int>	client_t;
			typedef std::set<char>	mode_t;
			typedef std::set<int>	invite_t;

		private:
			Server*				_server;
			const std::string	_name;
			std::string			_topic;
			client_t			_clients;
			mode_t				_modes;
			invite_t			_invites;

		public:
			Channel(Server* server, const std::string name);
			~Channel();
			
			bool	isMember(const Client* client);
			bool	hasMode(const char c);
			void	addClient(const Client* client);
			void	rmClient(const Client* client);

			const std::string&	getName() const;
			const std::string&	getTopic() const;
			const client_t&		getClients() const;
			const mode_t&		getModes() const;
			std::string			getModestr() const;
			std::string			getMembers() const;

			void	setTopic(const std::string& topic);
			void	setModes(const std::string& modes);
			void	setMode(const char c);
			void	unsetModes(const std::string& modes);
			void	unsetMode(const char c);
			void	inviteMember(Client* client);
	};
}

#endif