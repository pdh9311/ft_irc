/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:22:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/22 15:30:07 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#define DBGV(err,res,str)	(irc::x_void(err, res, str, __FILE__, __LINE__))
#define DBG(err,res,str)	(irc::x_int(err, res, str, __FILE__, __LINE__))

#define DBG_OFS(offset,str)	(irc::x_line(str, __FILE__, __LINE__ - offset))

#define PE(str)				(irc::perror(str, __FILE__, __LINE__));

namespace irc
{
	int	x_int(int err, int res, std::string str, std::string file, int line);

	void*	x_void(void* err, void* res, std::string str, std::string file,
																	int line);

	void	x_line(std::string str, std::string file, int line);

	void	perror(std::string err, std::string file, int line);
}