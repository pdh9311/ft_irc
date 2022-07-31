#include "Config.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <cstring>
#include <cstdlib>
#include <unistd.h>

// public funcs
namespace irc
{
	Config::Config()
	{
		type_parsing();
	}

		MachineInfo			Config::get_M() const	{ return _machine_info; }
		AdministrativeInfo	Config::get_A() const	{ return _administrative_info; }
		PortConnections		Config::get_P() const	{ return _port_connections; }
		ConnectionClasses	Config::get_Y() const	{ return _connection_classes; }
		ClientConnections	Config::get_Ii() const	{ return _client_connections; }
		OperatorPrivileges	Config::get_O() const	{ return _operator_privileges; }
		RestrictLines		Config::get_R() const	{ return _restrict_lines; }
		ExcludedAccounts	Config::get_Kk() const	{ return _excluded_accounts; }
		ServerConnections	Config::get_CcN() const	{ return _server_connections; }
		DenyAutoConnections	Config::get_D() const	{ return _deny_auto_connections; }
		HubConnections		Config::get_H() const	{ return _hub_connections; }
		LeafConnections		Config::get_L() const	{ return _leaf_connections; }
		VersionLimitations	Config::get_V() const	{ return _version_limitations;}
		// ExcludedMachines	Config::get_Q() const	{ return _excluded_machine; }
		ServiceConnections	Config::get_S() const	{ return _service_connections; }
		BounceServer 		Config::get_B() const	{ return _bounce_server; }
		DefaultLocalServer	Config::get_U() const	{ return _default_local_server; }
}

// private funcs
namespace irc
{
	void Config::type_parsing()
	{
		std::ifstream file(FILE_NAME);
		std::string s;
		char buf[BUFFER_SIZE];

		if (!file.is_open())
		{
			std::cout << "file not found" << std::endl;
			return ;
		}
		while (!file.eof())
		{
			file.getline(buf, BUFFER_SIZE);
			std::string str(buf);

			if(std::strchr(CONF_SPECIFY, buf[0]) != 0)
			{
				_words.clear();
				_words = colon_split(str);
				while (_words.size() < MAX_LEN)
					_words.push_back("");
				switch (buf[0])
				{
					case 'M':
						machine_information(); break;
					case 'A':
						administrative_info(); break;
					case 'P':
						port_connections(); break;
					case 'Y':
						connection_classes(); break;
					case 'I': case 'i':
						client_connections(); break;
					case 'O':
						operator_privileges(); break;
					case 'R':
						restrict_lines(); break;
					case 'K': case 'k':
						excluded_accounts(); break;
					case 'C': case 'c': case 'N':
						server_connections(); break;
					case 'D':
						deny_auto_connections(); break;
					case 'H':
						hub_connections(); break;
					case 'L':
						leaf_connections(); break;
					case 'V':
						version_limitations(); break;
					// case 'Q':
					// 	excluded_machines(); break; // NOT FORMAT
					case 'S':
						service_connections(); break;
					case 'B':
						bounce_server(); break;
					case 'U':
						default_local_server(); break;
				}
			}
		}
	}

	void Config::administrative_info()
	{
		_administrative_info.setMember(_words[1], _words[2], _words[3]);
	}

	void Config::connection_classes()
	{
		_connection_classes.setMember(
			std::atoi(_words[1].c_str()),
			std::atoi(_words[2].c_str()),
			std::atoi(_words[3].c_str()),
			std::atoi(_words[4].c_str()),
			std::atoi(_words[5].c_str()),
			std::atoi(_words[6].c_str()),
			std::atoi(_words[7].c_str()));
	}


	void Config::operator_privileges()
	{
		_operator_privileges.setMember(
			_words[1],
			_words[2],
			_words[3],
			std::atoi(_words[4].c_str()),
			_words[5]);
	}

	void Config::excluded_accounts()
	{
		_excluded_accounts.setMember(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	}

	void Config::deny_auto_connections()
	{
		_deny_auto_connections.setMember(_words[1], _words[2], _words[3], _words[4]);
	}

	void Config::leaf_connections()
	{
		_leaf_connections.setMember(_words[1], _words[3], std::atoi(_words[4].c_str()));
	}

	//void Config::ExcludedMachines()
	// {
	// 	std::string str(s);
	// 	_words.clear();
	// 	_words = colon_split(str);
	// while (_words.size() < MAX_LEN)
	// 		_words.push_back("");
	// 	_machine_info.setMember(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	// }

	void Config::bounce_server()
	{
		_bounce_server.setMember(_words[1],  _words[3], std::atoi(_words[4].c_str()));
	}
	////////////////////////////////////////////////////////////////////////////////////////
	void Config::machine_information()
	{
		_machine_info.setMember(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	}
	void Config::port_connections()
	{
		_port_connections.setMember(_words[1], _words[3], std::atoi(_words[4].c_str()));
	}
	void Config::client_connections()
	{
		_client_connections.setMember(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()), _words[5]);
	}
	void Config::restrict_lines()
	{
		_restrict_lines.setMember(_words[1], _words[2], _words[3]);
	}
	void Config::server_connections()
	{
		_server_connections.setMember(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()), _words[5]);
	}
	void Config::hub_connections()
	{
		_hub_connections.setMember(_words[1], _words[2]);
	}
	void Config::version_limitations()
	{
		_version_limitations.setMember(_words[1], _words[2], _words[3]);
	}
	void Config::service_connections()
	{
		_service_connections.setMember(_words[1], _words[2], _words[3], _words[4], _words[5]);
	}
	void Config::default_local_server()
	{
		_default_local_server.setMember(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	}

	std::vector<std::string> Config::colon_split(std::string& str)
	{
		std::vector<std::string> _words;
		std::string delim = ":";
		size_t pos = 0;

		while ((pos = str.find(delim)) != std::string::npos)
		{
			_words.push_back(str.substr(0, pos));
			str.erase(0, pos + delim.size());
		}
		return _words;
	}
}
