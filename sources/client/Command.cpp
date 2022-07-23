#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/cmds/cmds.hpp"

#include <iostream>

namespace irc
{
	Command::hashmap_t	Command::build_hashmap()
	{
		Command::hashmap_t	ht;
		/*	Connection Registration	*/
		ht["USER"] 		= cmd::user;
		ht["NICK"] 		= cmd::nick;
		ht["SERVER"]	= cmd::server;
		ht["OPER"]		= cmd::oper;
		ht["QUIT"]		= cmd::quit;
		ht["SQUIT"]		= cmd::squit;

		/*	Channel operations	*/
		// ht["JOIN"]		= cmd::join;
		// ht["PART"]		= cmd::part;
		// ht["MODE"]		= cmd::mode;
		// ht["TOPIC"]		= cmd::topic;
		// ht["NAMES"]		= cmd::names;
		// ht["LIST"]		= cmd::list;
		// ht["INVITE"]	= cmd::invite;
		// ht["KICK"]		= cmd::kick;
	
		/*	Server queries and commands	*/
		// ht["VERSION"]	= cmd::version;
		// ht["STATS"]		= cmd::stats;
		// ht["LINKS"]		= cmd::links;
		// ht["TIME"]		= cmd::time;
		// ht["CONNECT"]	= cmd::connect;
		// ht["TRACE"]		= cmd::trace;
		// ht["ADMIN"]		= cmd::admin;
		// ht["INFO"]		= cmd::info;

		/*	Sending messages	*/
		// ht["PRIVMSG"]	= cmd::privmsg;
		// ht["NOTICE"]	= cmd::notice;

		/*	User-based queries	*/
		// ht["WHO"]		= cmd::who;
		// ht["WHOIS"]		= cmd::whois;
		// ht["WHOWAS"]	= cmd::whowas;

		/*	Miscellaneous messages	*/
		// ht["KILL"]		= cmd::kill;
		// ht["PING"]		= cmd::ping;
		// ht["PONG"]		= cmd::pong;
		// ht["ERROR"]		= cmd::error;

		/*	Optional messages	*/ 
		// ht["AWAY"]		= cmd::away;
		// ht["REHASH"]	= cmd::rehash;
		// ht["RESTART"]	= cmd::restart;
		// ht["SUMMON"]	= cmd::summon;
		// ht["USERS"]		= cmd::users;
		// ht["WALLOPS"]	= cmd::operwall;
		// ht["USERHOST"]	= cmd::userhost;
		// ht["ISON"]		= cmd::ison;

		return (ht);
	}

	void	Command::parse(const std::string& str)
	{
		std::cout << "command::parse called for [" << str << "]" << std::endl;
		size_t	cur = 0;
		size_t	fpos;
		// std::string					prefix;
		// std::string					cmd;
		// // std::string					arg;
		// std::vector<std::string>	args;

		if (str[cur] == ':') // has prefix
		{
			fpos = str.find(' ', ++cur);
			_prefix = str.substr(cur, fpos - cur);
			cur = fpos;
		} // is message with only prefix valid? 

		while (str[cur] == ' ') cur++;

		fpos = str.find(' ', cur);
		_command = str.substr(cur, fpos - cur);
		cur = fpos;

		while (cur != std::string::npos)
		{
			while (str[cur] == ' ') cur++;
			if (str[cur] == ':')
				fpos = std::string::npos;
			else
				fpos = str.find(' ', cur);
			// arg = str.substr(cur, fpos - cur);
			_args.push_back(str.substr(cur, fpos - cur));
			cur = fpos;
		}

		// std::cout << "prefix: " << prefix << "#" << std::endl;
		// std::cout << "cmd: " << cmd << "#" <<  std::endl;
		// for(int i = 0; i < args.size(); ++i)
		// {
		// 	std::cout << "arg#" << i << ": " << args[i] << "#" <<  std::endl;
		// }

		// _cmds.push_back(Command(prefix, cmd, args));

	}

	void	Command::setFunc()
	{
		hashmap_t::iterator fit = hashmap.find(_command);

		if (!_command.empty() && fit != hashmap.end())
			_func = fit->second;
	}

}

namespace irc
{
	Command::Command(Client* c, Server* s, const std::string cstr)
	:	_client(c), _server(s), _result(""), _func(0)
	{
		this->parse(cstr);
		// if (Command::hashmap.empty())
		// 	Command::hashmap = build_hashmap();
		this->setFunc();
	}

	Command::~Command()
	{}

	void	Command::run()
	{
		std::cout << "command::run" << std::endl;
		if (_func) // do we need default action?
			this->_func(this);
		if (!_result.empty()) // check default action for invalid cmd
			_server->queue(_client->getFD(), _result);	
	}

	Client*	Command::getClient()
	{
		return (_client);
	}

	Server*	Command::getServer()
	{
		return (_server);
	}

	const std::string&	Command::getPrefix()
	{
		return (_prefix);
	}

	const std::string&	Command::getCommand()
	{
		return (_command);
	}

	const std::vector<std::string>&	Command::getArgs()
	{
		return (_args);
	}

	void	Command::setResult(const std::string& rstr)
	{
		_result = rstr;
	}
}