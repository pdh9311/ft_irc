/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:22:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/18 15:35:44 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#define XV(err,res,str)	(ft::x_void(err,res,str,__FILE__,__LINE__))
#define X(err,res,str)	(ft::x_int(err,res,str,__FILE__,__LINE__))

namespace ft
{
	int	x_int(int err, int res, std::string str, std::string file, int line);

	void	*x_void(void* err, void* res, std::string str, std::string file,
	int line);
}