#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

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

#include <vector>

# define BUFFER_SIZE 512
# define FILE_NAME "irc.conf"
# define MAX_LEN 10
# define CONF_SPECIFY "MAPYIiORKkCcNDHLVQSBU"

namespace irc
{
	class Config
	{
	 	private:
			MachineInfo					_machine_info;			// M
			AdministrativeInfo			_administrative_info;	// A
			PortConnections				_port_connections;		// P
			ConnectionClasses			_connection_classes;	// Y
			ClientConnections			_client_connections;	// I,i
			OperatorPrivileges			_operator_privileges;	// O
			RestrictLines				_restrict_lines;		// R
			ExcludedAccounts			_excluded_accounts;		// K,k
			ServerConnections			_server_connections;	// C,c,N
			DenyAutoConnections			_deny_auto_connections;	// D
			HubConnections				_hub_connections;		// H
			LeafConnections				_leaf_connections;		// L
			VersionLimitations			_version_limitations;	// V
			// ExcludedMachines			_excluded_machines;		// Q
			ServiceConnections			_service_connections;	// S
			BounceServer 				_bounce_server;			// B
			DefaultLocalServer			_default_local_server;	// U
			std::vector<std::string>	_words;

			void	type_parsing();
			void	machine_information();
			void	administrative_info();
			void	port_connections();
			void	connection_classes();
			void	client_connections();
			void	operator_privileges();
			void	restrict_lines();
			void	excluded_accounts();
			void	server_connections();
			void	deny_auto_connections();
			void	hub_connections();
			void	leaf_connections();
			void	version_limitations();
			void	ExcludedMachines();
			void	service_connections();
			void	bounce_server();
			void	default_local_server();

			std::vector<std::string>	colon_split(std::string& str);
		public:
			Config();

			MachineInfo			get_M();
			AdministrativeInfo	get_A();
			PortConnections		get_P();
			ConnectionClasses	get_Y();
			ClientConnections	get_Ii();
			OperatorPrivileges	get_O();
			RestrictLines		get_R();
			ExcludedAccounts	get_Kk();
			ServerConnections	get_CcN();
			DenyAutoConnections	get_D();
			HubConnections		get_H();
			LeafConnections		get_L();
			VersionLimitations	get_V();
			// ExcludedMachines	get_Q();
			ServiceConnections	get_S();
			BounceServer 		get_B();
			DefaultLocalServer	get_U();
	};

}

#endif
