/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:42:57 by minsunki          #+#    #+#             */
/*   Updated: 2022/07/21 17:44:08 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "irc_type/MachineInfo.hpp"
#include "irc_type/AdministrativeInfo.hpp"
#include "irc_type/PortConnections.hpp"
#include "irc_type/ConnectionClasses.hpp"
#include "irc_type/ClientConnections.hpp"
#include "irc_type/OperatorPrivileges.hpp"
#include "irc_type/RestrictLines.hpp"
#include "irc_type/ExcludedAccounts.hpp"
#include "irc_type/ServerConnections.hpp"
#include "irc_type/DenyAutoConnections.hpp"
#include "irc_type/HubConnections.hpp"
#include "irc_type/LeafConnections.hpp"
#include "irc_type/VersionLimitations.hpp"
//ExcludedMachines
#include "irc_type/ServiceConnections.hpp"
#include "irc_type/BounceServer.hpp"
#include "irc_type/DefaultLocalServer.hpp"

# define BUFFER_SIZE 512
# define FILE_NAME "irc.conf"

namespace irc
{
	class Config
	{
	 	public:
			MachineInfo			_machine_info;	// M
			AdministrativeInfo	_administrative_info; // A
			PortConnections		_port_connections;	//P
			ConnectionClasses	_connection_classes;// Y
			ClientConnections	_client_connections;	// I,i
			OperatorPrivileges	_operator_privileges; // O
			RestrictLines		_restrict_lines;	// R
			ExcludedAccounts	_excluded_accounts;// K,k
			ServerConnections	_server_connections;	// C,c,N
			DenyAutoConnections	_deny_auto_connections;// D
			HubConnections		_hub_connections;	// H
			LeafConnections		_leaf_connections;// L
			VersionLimitations	_version_limitations;	// V
			// ExcludedMachines	_excluded_machines// Q
			ServiceConnections	_service_connections;	// S
			BounceServer 		_bounce_server;	// B
			DefaultLocalServer	_default_local_server;	// U

			Config();

		private:
			std::vector<std::string> _words;

			void type_parsing();
			void machine_information(const char* s);
			void administrative_info(const char* s);
			void port_connections(const char* s);
			void connection_classes(const char* s);
			void client_connections(const char* s);
			void operator_privileges(const char* s);
			void restrict_lines(const char* s);
			void excluded_accounts(const char* s);
			void server_connections(const char* s);
			void deny_auto_connections(const char* s);
			void hub_connections(const char* s);
			void leaf_connections(const char* s);
			void version_limitations(const char* s);
			//	ExcludedMachines(const char* s);
			void service_connections(const char* s);
			void bounce_server(const char* s);
			void default_local_server(const char* s);

			std::vector<std::string> colon_split(std::string& str);
		public:

	};

}


#endif