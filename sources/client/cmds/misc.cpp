/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:14 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/25 16:10:50 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/numerics.hpp"

#include <ctime>

namespace irc
{
	namespace cmd
	{
		void	kill	(Command* cmd)
		{

		}

		void	ping	(Command* cmd)
		{
			// client should not call ping command. Ignore?
		}
		
		void	pong	(Command* cmd)
		{
			const std::string& a1 = cmd->getArgs()[0];
			if (a1.empty())
				return (cmd->setResult(ERR_NOORIGIN));
			cmd->getClient()->setLastPing(std::time(0)); // does pong arg have to match nick?
		}

		void	error	(Command* cmd)
		{

		}
	}
}