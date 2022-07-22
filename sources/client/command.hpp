/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:45:07 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/22 14:13:53 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <vector>
#include <string>

namespace ft::irc
{
	class Command
	{
		private:
			const std::string				_prefix;
			const std::string				_command;
			const std::vector<std::string>	_args;
				

		public:
			Command(const std::string& p, const std::string& c,
											const std::vector<std::string>& a);
			virtual	~Command();

			
	};
}

#endif