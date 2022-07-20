/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:30:08 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 01:17:08 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "debug.hpp"
#include <iostream>
#include <cerrno>
#include <cstring>
// #include <errno.h>

namespace ft
{
	int	x_int(int err, int res, std::string str, std::string file, int line)
	{
		if (res == err)
		{
			std::cerr << str << " error (" << file << ", " << line << "): ";
			std::cerr << std::strerror(errno) << std::endl;

			exit (1);
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

			exit (1);
		}
		return (res);
	}

	void	x_line(std::string str, std::string file, int line)
	{
		std::cerr << str << " error (" << file << ", " << line << "): ";
		std::cerr << std::strerror(errno) << std::endl;
		exit (1);
	}
	
	void	perror(std::string err, std::string file, int line)
	{
		std::cerr << err << std::endl;
		std::cerr << " (" << file << ", " << line << "): ";
		exit (1);
	}
}