/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:30 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/27 15:27:25 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "util.hpp"

#include <sstream>
#include <iomanip>

namespace irc
{
	int	stoi(const std::string& str)
	{
		int					ret;
		std::istringstream	ss(str);
		
		ss >> ret;
		return (ret);
	}

	std::string	to_string(const int& x)
	{
		std::stringstream	ss;
		ss << std::setfill('0');
		ss << std::setw(3);
		ss << x;
		return (ss.str());
	}
}