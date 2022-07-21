/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:08:35 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 17:43:47 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <vector>

namespace ft::irc
{
	class Channel
	{
		class Client;

		private:
			std::vector<Client*>	_clients;

		public:
			Channel();
			~Channel();
			
	};
}

#endif