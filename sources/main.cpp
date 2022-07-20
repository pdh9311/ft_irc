/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:08:16 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 01:30:36 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.hpp"
#include "util.hpp"
#include <iostream>
#include <string>

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " port" << std::endl;
		return (0);
	}

	ft::irc::Server	serv(argv[1]);

	serv.initialize();
	serv.run();
	return (0);
}