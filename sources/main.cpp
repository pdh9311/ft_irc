/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:08:16 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/23 22:35:54 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"
#include "client/Command.hpp"
#include "util.hpp"
#include <iostream>
#include <string>

irc::Command::hashmap_t	irc::Command::hashmap = Command::build_hashmap();

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " port" << std::endl;
		return (0);
	}

	irc::Server	serv(argv[1]);

	serv.initialize();
	serv.run();
	return (0);
}