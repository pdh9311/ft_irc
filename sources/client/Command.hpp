#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <vector>
#include <string>
#include <map>

namespace irc
{
	#define MAX_PARAMS	16
	// const static std::map<std::string, short>	cmdtab
	// {
	// 	{"PASS", PASS},
	// 	{"NICK", NICK},
	// 	{"USER", USER},
	// 	{"PONG", PONG},

	// 	{"WHO", WHO},
	// 	{"WHOIS", WHOIS},
	// 	{"QUIT", QUIT}
	// };
	class Server;
	class Client;

	class Command
	{
		public:
			// enum cenums
			// {
			// 	CAP,	// IRCv3?
			// 	PASS, NICK, USER, SERVER, OPER, QUIT, SQUIT,
			// 	JOIN, PART, MODE, TOPIC, NAMES, LIST, INVITE, KICK,
			// 	WHO, WHOIS, WHOWAS,
			// 	KILL, PING, PONG, ERROR
			// };
			typedef	void (*fp)(Command*);
			typedef	std::map<std::string, fp>	hashmap_t;
			static hashmap_t					build_hashmap();
			static hashmap_t					hashmap;

		private:
			Client*						_client;
			Server*						_server;
			std::string					_result;
			fp							_func;
			std::string					_prefix;
			std::string					_command;
			std::vector<std::string>	_args;


			void	parse(const std::string& str);
			void	setFunc();

		public:

			Command(Client* client, Server* server, const std::string cstr);
			virtual	~Command();

			void	run();

			Client*							getClient();
			Server*							getServer();
			const std::string&				getPrefix();
			const std::string&				getCommand();
			const std::vector<std::string>&	getArgs();
			int								getArgC();

			void	queue(const std::string msg);
			void	queue(const short& rcods, const std::string msg);

			void	setResult(const std::string& rstr);
			void	setResult(const short& rcode, const std::string s1 = "");

	};
}

#endif
