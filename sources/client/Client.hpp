/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:47:58 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/27 15:00:38 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <string>
#include <vector>
#include <set>

#include <unistd.h>

namespace irc
{
	class Channel;
	class Server;
	class Command;

	class Client
	{
		friend class Server;

		public:
			typedef std::set<char>	mode_t;
		
		private:
			const int		_fd;
			Server*		 	_server;
			Channel*		_cchannel;
			time_t			_last_ping; // initialized up to here

			// std::vector<Command>	_cmds;
			std::string		_buf;
			std::string		_nick;
			std::string		_user_name;
			std::string		_real_name;
			std::string		_last_nick;
			mode_t			_modes;

			// void	_parse(std::string str);
			int		parse();
			
		public:
			Client (const int& fd, Server* server);
			virtual	~Client();

			void	recv();

			const int&			getFD() const;
			const time_t&		getLastPing() const;
			const std::string&	getNick() const;
			const std::string&	getUserName() const;
			const std::string&	getRealName() const;
			const mode_t&		getModes() const;
			const Channel*		getCChannel() const;
			bool				hasMode(char c) const;

			void	setLastPing(const time_t& time);
			void	setNick(const std::string& str);
			void	setUserName(const std::string& name);
			void	setRealName(const std::string& name);
			void	setModes(const std::string& modes);
			void	unsetModes(const std::string& modes);
			void	setCChannel(Channel* channel);
	};
}

#endif