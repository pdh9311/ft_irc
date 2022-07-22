/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:30:08 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/22 15:35:37 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "debug.hpp"
#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdlib>

// #include <unistd.h>
// #include <errno.h>

namespace irc
{
	int	x_int(int err, int res, std::string str, std::string file, int line)
	{
		if (res == err)
		{
			std::cerr << str << " error (" << file << ", " << line << "): ";
			std::cerr << std::strerror(errno) << std::endl;

			std::exit (1);
		}
		return (res);
	}

	void*	x_void(void* err, void* res, std::string str, std::string file,
																	int line)
	{
		if (res == err)
		{
			std::cerr << str << " error (" << file << ", " << line << "): ";
			std::cerr << std::strerror(errno) << std::endl;

			std::exit (1);
		}
		return (res);
	}

	void	x_line(std::string str, std::string file, int line)
	{
		std::cerr << str << " error (" << file << ", " << line << "): ";
		std::cerr << std::strerror(errno) << std::endl;
		std::exit (1);
	}
	
	void	perror(std::string err, std::string file, int line)
	{
		std::cerr << err << std::endl;
		std::cerr << " (" << file << ", " << line << "): ";
		std::exit (1);
	}
}