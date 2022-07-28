/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:40 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/28 14:40:08 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <string>

namespace irc
{
	int			stoi(const std::string& str);
	std::string	to_string(const int& x);
	bool		isLetterC(const char c);
	bool		isLetterStr(const std::string& str);
	bool		isDigitC(const char c);
	bool		isDigitStr(const std::string& str);
	bool		isUserC(const char c);
	bool		isUserStr(const std::string& str);
	bool		isHexDigitC(const char c);
	bool		isHexDigitStr(const std::string& str);
	bool		isSpecialC(const char c);
	bool		isSpecialStr(const std::string& str);
	bool		isNickStr(const std::string& str);
}