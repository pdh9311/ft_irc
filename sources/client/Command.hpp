#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <vector>
#include <string>
#include <map>

namespace irc
{
	#define MAX_PARAMS	16

	class Server;
	class Client;

	class Command
	{
		public:
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
			std::string					_trailing;
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
			const std::string&				getTrailing();
			const std::vector<std::string>&	getArgs();
			int								getArgC();

			void	queue(const std::string msg);
			void	queue(const short& rcode, const std::string msg);
			void	queue(const short& rcode);

			void	setResult(const std::string& rstr);
			void	setResult(const short& rcode, const std::string s1 = "");
	};
}

#endif
