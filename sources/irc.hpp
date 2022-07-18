/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:25:10 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/18 16:35:27 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <string>
#include <sys/poll.h>

namespace ft
{
	class irc
	{
		private:
			std::vector<struct pollfd>	_pfds;
			const int					_port;
			int							_lfd;

		public:
			irc(std::string port);
			virtual	~irc();

			void	accept();
			void	read(struct pollfd& pfd);
			void	initialize();
			void	loop();

	};
}