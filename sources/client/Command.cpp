#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/cmds/cmds.hpp"

namespace irc
{
	Command::hashmap_t	Command::build_hashmap()
	{
		Command::hashmap_t	_ht;
		/*	connection	*/
		_ht["USER"] 	= cmd::user;
		_ht["NICK"] 	= cmd::nick;
		_ht["SERVER"]	= cmd::server;
		_ht["OPER"]		= cmd::oper;
		_ht["QUIT"]		= cmd::quit;
		_ht["SQUIT"]	= cmd::squit;

		/*	blabla	*/

		return (_ht);
	}

	void	Command::parse(const std::string& str)
	{
	// std::cout << "_parse called for [" << str << "]" << std::endl;
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
	:	_client(c), _server(s), _result(0), _func(0)
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
		if (this->_func) // do we need default action?
			this->_func(*this);
		
		// std::map<std::string, fp>::iterator fit = _ht.find(_command);
		// if (fit != _ht.end())
		// {
		// 	(fit->second)(*this);
		// }
	}

	Client*	Command::getClient()
	{
		return (this->_client);
	}

	Server*	Command::getServer()
	{
		return (this->_server);
	}

	const std::string&	Command::getPrefix()
	{
		return (this->_prefix);
	}

	const std::string&	Command::getCommand()
	{
		return (this->_command);
	}

	const std::vector<std::string>&	Command::getArgs()
	{
		return (this->_args);
	}
}