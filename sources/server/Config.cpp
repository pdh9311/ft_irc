#include "Config.hpp"

#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <vector>

// public funcs
namespace irc
{
	Config::Config()
	{
		type_parsing();
	}
}

// private funcs
namespace irc
{
	void Config::type_parsing()
	{
		// char	dir[512];
		// getcwd(dir, sizeof(dir));
		// std::string	dirpath = dir;
		// std::string filepath = dirpath + "/irc.conf";
		std::ifstream file(FILE_NAME);
		std::string s;
		char buf[BUFFER_SIZE];

		// std::cout << filepath << std::endl;
		if (!file.is_open())
		{
			std::cout << "file not found" << std::endl;
			return ;
		}
		while (file)
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
				std::cout << buf <<std:: endl;
			}
		}
	}

	void Config::administrative_info()
	{
		_administrative_info.set_member(_words[1], _words[2], _words[3]);
	}

	void Config::connection_classes()
	{
		_connection_classes.set_member(
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
		_operator_privileges.set_member(
			_words[1],
			_words[2],
			_words[3],
			std::atoi(_words[4].c_str()),
			_words[5]);
	}

	void Config::excluded_accounts()
	{
		_excluded_accounts.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	}

	void Config::deny_auto_connections()
	{
		_deny_auto_connections.set_member(_words[1], _words[2], _words[3], _words[4]);
	}

	void Config::leaf_connections()
	{
		_leaf_connections.set_member(_words[1], _words[3], std::atoi(_words[4].c_str()));
	}

	//void Config::ExcludedMachines()
	// {
	// 	std::string str(s);
	// 	_words.clear();
	// 	_words = colon_split(str);
	// while (_words.size() < MAX_LEN)
	// 		_words.push_back("");
	// 	_machine_info.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	// }

	void Config::bounce_server()
	{
		_bounce_server.set_member(_words[1],  _words[3], std::atoi(_words[4].c_str()));
	}
	////////////////////////////////////////////////////////////////////////////////////////
	void Config::machine_information()
	{
		_machine_info.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	}
	void Config::port_connections()
	{
		_port_connections.set_member(_words[1], _words[3], std::atoi(_words[4].c_str()));
	}
	void Config::client_connections()
	{
		_client_connections.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()), _words[5]);
	}
	void Config::restrict_lines()
	{
		_restrict_lines.set_member(_words[1], _words[2], _words[3]);
	}
	void Config::server_connections()
	{
		_server_connections.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()), _words[5]);
	}
	void Config::hub_connections()
	{
		_hub_connections.set_member(_words[1], _words[2]);
	}
	void Config::version_limitations()
	{
		_version_limitations.set_member(_words[1], _words[2], _words[3]);
	}
	void Config::service_connections()
	{
		_service_connections.set_member(_words[1], _words[2], _words[3], _words[4], _words[5]);
	}
	void Config::default_local_server()
	{
		_default_local_server.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
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