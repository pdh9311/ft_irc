/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:45:07 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/22 15:28:57 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <vector>
#include <string>
#include <map>

namespace irc
{
	// const static std::map<std::string, short>	cmdtab
	// {
	// 	{"PASS", PASS},
	// 	{"NICK", NICK},
	// 	{"USER", USER},
	// 	{"PONG", PONG},

	// 	{"WHO", WHO},
	// 	{"WHOIS", WHOIS},
	// 	{"QUIT", QUIT}
	// };
	class Command
	{
		public:
			// enum cenums
			// {
			// 	CAP,	// IRCv3?
			// 	PASS, NICK, USER, SERVER, OPER, QUIT, SQUIT,
			// 	JOIN, PART, MODE, TOPIC, NAMES, LIST, INVITE, KICK,
			// 	WHO, WHOIS, WHOWAS,
			// 	KILL, PING, PONG, ERROR
			// };

		private:
			const std::string				_prefix;
			const std::string				_command;
			// const std::string				_commandstr;
			// const unsigned short			_command;
			const std::vector<std::string>	_args;
				

		public:

			Command(const std::string& p, const std::string& c,
											const std::vector<std::string>& a);
			virtual	~Command();

			
	};
}

#endif