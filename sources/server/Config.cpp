#include "Config.hpp"

#include <cstdlib>

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
		std::ifstream file(FILE_NAME);
		std::string s;
		char buf[BUFFER_SIZE];

		if (!file.is_open())
		{
			std::cout << "file not found" << std::endl;
			return ;
		}
		while (file)
		{
			file.getline(buf, BUFFER_SIZE);
			switch (buf[0])

			{
				case 'M':
					machine_information(buf); break;
				case 'A':
					administrative_info(buf); break;
				case 'P':
					port_connections(buf); break;
				case 'Y':
					connection_classes(buf); break;
				case 'I': case 'i':
					client_connections(buf); break;
				case 'O':
					operator_privileges(buf); break;
				case 'R':
					restrict_lines(buf); break;
				case 'K': case 'k':
					excluded_accounts(buf); break;
				case 'C': case 'c': case 'N':
					server_connections(buf); break;
				case 'D':
					deny_auto_connections(buf); break;
				case 'H':
					hub_connections(buf); break;
				case 'L':
					leaf_connections(buf); break;
				case 'V':
					version_limitations(buf); break;
				// case 'Q':
				// 	excluded_machines(buf); break; // NOT FORMAT
				case 'S':
					service_connections(buf); break;
				case 'B':
					bounce_server(buf); break;
				case 'U':
					default_local_server(buf); break;
			}
		}
	}

	void Config::administrative_info(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_administrative_info.set_member(_words[1], _words[2], _words[3]);
	}

	void Config::connection_classes(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_connection_classes.set_member(
			std::atoi(_words[1].c_str()),
			std::atoi(_words[2].c_str()),
			std::atoi(_words[3].c_str()),
			std::atoi(_words[4].c_str()),
			std::atoi(_words[5].c_str()),
			std::atoi(_words[6].c_str()),
			std::atoi(_words[7].c_str()));
	}


	void Config::operator_privileges(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_operator_privileges.set_member(
			_words[1],
			_words[2],
			_words[3],
			std::atoi(_words[4].c_str()),
			_words[5]);
	}

	void Config::excluded_accounts(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_excluded_accounts.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	}

	void Config::deny_auto_connections(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_deny_auto_connections.set_member(_words[1], _words[2], _words[3], _words[4]);
	}

	void Config::leaf_connections(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_leaf_connections.set_member(_words[1], _words[3], std::atoi(_words[4].c_str()));
	}

	//void Config::ExcludedMachines(const char* s)
	// {
	// 	std::string str(s);
	// 	_words.clear();
	// 	_words = colon_split(str);
	// 	_machine_info.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	// }

	void Config::bounce_server(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_bounce_server.set_member(_words[1],  _words[3], std::atoi(_words[4].c_str()));
	}
	////////////////////////////////////////////////////////////////////////////////////////
	void Config::machine_information(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_machine_info.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()));
	}
	void Config::port_connections(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_port_connections.set_member(_words[1], _words[3], std::atoi(_words[4].c_str()));
	}
	void Config::client_connections(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_client_connections.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()), _words[5]);
	}
	void Config::restrict_lines(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_restrict_lines.set_member(_words[1], _words[2], _words[3]);
	}
	void Config::server_connections(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_server_connections.set_member(_words[1], _words[2], _words[3], std::atoi(_words[4].c_str()), _words[5]);
	}
	void Config::hub_connections(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_hub_connections.set_member(_words[1], _words[2]);
	}
	void Config::version_limitations(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_version_limitations.set_member(_words[1], _words[2], _words[3]);
	}
	void Config::service_connections(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
		_service_connections.set_member(_words[1], _words[2], _words[3], _words[4], _words[5]);
	}
	void Config::default_local_server(const char* s)
	{
		std::string str(s);
		_words.clear();
		_words = colon_split(str);
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