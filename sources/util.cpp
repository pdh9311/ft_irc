/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:30 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/25 15:02:45 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "util.hpp"
#include <sstream>

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
		ss << x;
		return (ss.str());
	}
}