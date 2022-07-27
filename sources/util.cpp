/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:30 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/28 00:09:52 by minsunki         ###   ########seoul.kr  */
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

	bool	isLetterStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!(('a' <= *it && *it <= 'z') || ('A' <= *it && *it <= 'Z')))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isDigitStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!('0' <= *it && *it <= '9'))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isUserStr(const std::string& str)
	{
		std::string::const_iterator it = str.begin();

		while (it != str.end())
		{
			if (*it == 0 || *it == '\r' || *it == '\n' || *it == ' ' || *it == '@')
				return (false);
			++it;
		}
		return (true);
	}

	bool	isHexDigitStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!('0' <= *it && *it <= '9') && !('A' <= *it && *it <= 'F'))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isSpecialStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!(0x5b <= *it && *it <= 0x60) && !(0x7b <= *it && *it <= 0x7d))
				return (false);
			++it;
		}
		return (true);
	}
}