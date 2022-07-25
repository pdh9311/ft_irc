/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:40 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/25 15:01:39 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <string>

namespace irc
{
	int			stoi(const std::string& str);
	std::string	to_string(const int& x);
}