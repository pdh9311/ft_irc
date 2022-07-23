/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:47:58 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/23 21:55:09 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <string>
#include <vector>

#include <unistd.h>

namespace irc
{
	class Server;

	class Command;

	class Client
	{
		friend class Server;
		
		private:
			const int		_fd;
			Server*		 	_server; // is this the right const?
			time_t			_last_ping; // initialized up to here

			// std::vector<Command>	_cmds;
			std::string		_buf;
			std::string		_nick;
			std::string		_last_nick;

			void	_parse(std::string str);
			int		parse();
			
		public:
			Client (const int& fd, Server* server);
			virtual	~Client();

			void	recv();

			const int&				getFD() const;
			const time_t&			getLastPing() const;
			// std::vector<Command>&	getCommands();

			// void	setLastPing(const time_t& time);

			void	setNick(const std::string& str);

	};
}

#endif