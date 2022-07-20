/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:47:58 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 01:43:48 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <string>

#include <unistd.h>

namespace ft::irc
{
	class Client
	{
		private:
			const int	_fd;
			std::string	_buf;
			std::string	_nick;

		public:
			Client (const int& fd);
			virtual	~Client();

			void	recv();

			const int&	getFD() const;
	};
}

#endif