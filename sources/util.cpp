/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:30 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/22 15:29:23 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "util.hpp"
#include <sstream>

namespace irc
{
	int	stoi(std::string& str)
	{
		int					ret;
		std::istringstream	ss(str);
		
		ss >> ret;
		return (ret);
	}
}