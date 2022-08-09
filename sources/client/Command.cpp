#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"
#include "client/cmds/cmds.hpp"
#include "client/numerics.hpp"
#include "util.hpp"

// #include <string>
#include <iostream>
#include <algorithm>

namespace irc
{
	Command::hashmap_t	Command::build_hashmap()
	{
		Command::hashmap_t	ht;
		/*	Connection Registration	*/
		ht["PASS"]		= cmd::pass;
		ht["USER"] 		= cmd::user;
		ht["NICK"] 		= cmd::nick;
		ht["SERVER"]	= cmd::server;
		ht["OPER"]		= cmd::oper;
		ht["QUIT"]		= cmd::quit;
		ht["SQUIT"]		= cmd::squit;

		/*	Channel operations	*/
		ht["JOIN"]		= cmd::join;
		ht["PART"]		= cmd::part;
		ht["MODE"]		= cmd::mode;
		ht["TOPIC"]		= cmd::topic;
		ht["NAMES"]		= cmd::names;
		ht["LIST"]		= cmd::list;
		ht["INVITE"]	= cmd::invite;
		ht["KICK"]		= cmd::kick;

		/*	Server queries and commands	*/
		ht["MOTD"]		= cmd::motd;
		ht["LUSERS"]	= cmd::lusers;
		ht["VERSION"]	= cmd::version;
		ht["STATS"]		= cmd::stats;
		ht["LINKS"]		= cmd::links;
		ht["TIME"]		= cmd::time;
		ht["CONNECT"]	= cmd::connect;
		ht["TRACE"]		= cmd::trace;
		ht["ADMIN"]		= cmd::admin;
		ht["INFO"]		= cmd::info;

		/*	Sending messages	*/
		ht["PRIVMSG"]	= cmd::privmsg;
		ht["NOTICE"]	= cmd::notice;

		/*	User-based queries	*/
		ht["WHO"]		= cmd::who;
		ht["WHOIS"]		= cmd::whois;
		ht["WHOWAS"]	= cmd::whowas;

		/*	Miscellaneous messages	*/
		ht["KILL"]		= cmd::kill;
		ht["PING"]		= cmd::ping;
		ht["PONG"]		= cmd::pong;
		ht["ERROR"]		= cmd::error;

		/*	Optional messages	*/
		ht["AWAY"]		= cmd::away;
		ht["REHASH"]	= cmd::rehash;
		ht["RESTART"]	= cmd::restart;
		ht["SUMMON"]	= cmd::summon;
		ht["USERS"]		= cmd::users;
		ht["WALLOPS"]	= cmd::wallops;
		ht["USERHOST"]	= cmd::userhost;
		ht["ISON"]		= cmd::ison;

		return (ht);
	}

	void	Command::parse(const std::string& str)
	{
		// std::cout << "command::parse called for [" << str << "]" << std::endl;
		size_t	cur = 0;
		size_t	fpos;

		if (str[cur] == ':') // has prefix
		{
			fpos = str.find(' ', ++cur);
			_prefix = str.substr(cur, fpos - cur);
			cur = fpos;
		}

		while (str[cur] == ' ') cur++;

		fpos = str.find(' ', cur);
		_command = str.substr(cur, fpos - cur);
		for (size_t i = 0; i < _command.size(); ++i)
			_command[i] = std::toupper(_command[i]);

		cur = fpos;

		while (cur != std::string::npos)
		{
			while (str[cur] == ' ') cur++;
			if (str[cur] == ':')
				fpos = std::string::npos;
			else
				fpos = str.find(' ', cur);

			std::string	tmp = str.substr(cur, fpos - cur);
			if (!tmp.empty())
				_args.push_back(str.substr(cur, fpos - cur));
			cur = fpos;
		}

		if (_args.size() && _args.back()[0] == ':')
		{
			_trailing = _args.back().substr(1);
			_args.pop_back();
		}
	}

	void	Command::setFunc()
	{
		hashmap_t::iterator fit = hashmap.find(_command);

		if (!_command.empty() && fit != hashmap.end())
		{
			if (_client->getStatus() < Client::AUTH && _command != "PASS")
				return ;
			if (_client->getStatus() < Client::LOGGEDIN &&
				_command != "PASS" && !(_command == "NICK" || _command == "USER"))
				return ;

			_func = fit->second;
		}
	}

}

namespace irc
{
	Command::Command(Client* c, Server* s, const std::string cstr)
	:	_client(c), _server(s), _result(""), _func(0)
	{
		this->parse(cstr);
		this->setFunc();
	}

	Command::~Command()
	{}

	void	Command::run()
	{
		// std::cout << "command::run" << std::endl;
		if (_func)
			this->_func(this);
		if (!_result.empty()) // obsolete, left for compatibility
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

	const std::string&	Command::getTrailing()
	{
		return (_trailing);
	}

	const std::vector<std::string>&	Command::getArgs()
	{
		return (_args);
	}

	int	Command::getArgC()
	{
		return (_args.size());
	}

	void	Command::queue(const std::string msg) // messages w/o code
	{
		_client->queue(msg);
	}

	void	Command::queue(const short& rcode, const std::string msg)
	{
		std::string	str = _server->getPrefix(_client) + " ";
		str += (to_string(rcode) + " ");
		str += (_client->getNick() + " ");
		str += msg;

		_client->queue(str);
	}

	void	Command::queue(const short& rcode)
	{
		std::string str = _server->getPrefix(_client) + " ";
		str += (to_string(rcode) + " ");
		str += (_client->getNick() + " ");

		switch (rcode)
		{
			case ERR_NEEDMOREPARAMS:
				str += (getCommand() + " :Not enough parameters");
				break ;
			case ERR_NOPRIVILEGES:
				str += ":Permission Denied- You're not an IRC operator";
				break ;
			case ERR_USERSDONTMATCH:
				str += ":Cant change mode for other users";
				break ;
			case ERR_NOORIGIN:
				str += ":No origin specified";
				break ;
			case ERR_NOTEXTTOSEND:
				str += ":No text to send";
				break ;
			case RPL_LISTEND:
				str += ":End of /LIST";
				break ;
			default:
				str += ":Internal error Command::queue rcode";
		}

		_client->queue(str);
	}

	void	Command::setResult(const std::string& rstr) // obsolete
	{
		_result = rstr;
	}

	void	Command::setResult(const short& rcode, const std::string s1) //obsolete
	{
		_result = _server->getPrefix(_client) + " ";
		_result += to_string(rcode) + " ";
		_result += _client->getNick() + " ";

		// std::cout << _result << std::endl;
		switch (rcode)
		{
			case RPL_WELCOME:
				_result += ":Welcome to the Internet Relay Network " + s1 + "!" + _args[0] + "@" + _server->getName(); break ;
			case ERR_NOSUCHNICK:
				_result += _client->getNick() + " :No such nick/channel"; break ;
			// case ERR_NOSUCHSERVER:	//	TODO:: _server->getName()
			// 	_result += _server->getName() + " :No such server"; break ;
			case ERR_NOSUCHCHANNEL:
				_result += _args[0] + ":No such channel"; break ;
				// check if prefix on chan name needs to be removed.
			case ERR_CANNOTSENDTOCHAN:
				_result += _args[0] + ":Cannot send to channel"; break ;
				// same as above
			case ERR_TOOMANYCHANNELS:
				_result += _args[0] + "You have joined too many channels"; break ;
				 // saa
			case ERR_WASNOSUCHNICK:
				_result	= _args[0] + ":There was no such nickname"; break ;
			case ERR_TOOMANYTARGETS:
				_result += _args[0] + "Duplicate recipients. No message delievered"; break ;
			case ERR_NOORIGIN:
				_result	= ":No origin specified"; break ;
			case ERR_NORECIPIENT:
				_result	= ":No recipient given (" + _command + ")"; break;
				 // is <command> the command or entire str?
			case ERR_NOTEXTTOSEND:
				_result += ":No text to send"; break ;
			case ERR_NOTOPLEVEL:
				_result += _args[0] + " :No toplevel domain specified"; break ;
			case ERR_WILDTOPLEVEL:
				_result += _args[0] + " :Wildcard in toplevel domain"; break ;
			case ERR_UNKNOWNCOMMAND:
				_result += _command + " :Unknown command"; break ;
			case ERR_NOMOTD:
				_result += ":MOTD File is missing"; break ;
			// case ERR_NOADMININFO:
				// _result += _server->getName() + " :No administrative info available"; break ;
			case ERR_FILEERROR:
				_result += ":File error doing " + _args[0] + " on " + _args[1]; break ;
			case ERR_NONICKNAMEGIVEN:
				_result += "No nickname given"; break ;
			case ERR_ERRONEUSNICKNAME:
				_result += _args[0] + " :Erroneus nickname"; break ;
			case ERR_NICKNAMEINUSE:
				_result += _args[0] + " :Nickname is already in use"; break ;
			case ERR_NICKCOLLISION:
				_result += _args[0] + " :Nickname collision KILL"; break ;
			case ERR_USERNOTINCHANNEL:
				_result += _args[0] + " " + _args[1] + " :They aren't on that channel"; break ;
			case ERR_NOTONCHANNEL:
				_result += _args[0] + " :You're not on that channel"; break ;
			case ERR_USERONCHANNEL:
				_result += _args[0] + " " + _args[1] + " :is already on channel"; break ;
			case ERR_NOLOGIN:
				_result += _args[0] + " :User not logged in"; break ;
			case ERR_SUMMONDISABLED:
				_result += ":SUMMON has been disabled"; break ;
			case ERR_USERDISABLED:
				_result += ":USERS has been disabled"; break ;
			case ERR_NOTREGISTERED:
				_result += ":You have not registered"; break ;
			case ERR_NEEDMOREPARAMS:
				_result += _command + " :Not enough parameters"; break ;
			case ERR_ALREADYREGISTRED:
				_result += ":You may not reregister"; break ;
			case ERR_NOPERMFORHOST:
				_result += ":Your host isn't among the privileged"; break ;
			case ERR_PASSWDMISMATCH:
				_result += ":Password incorrect"; break ;
			case ERR_YOUREBANNEDCREEP:
				_result += ":You are banned from this server"; break ;
			case ERR_KEYSET:
				_result += _args[0] + " :Channel key already set"; break ;
			case ERR_CHANNELISFULL:
				_result += _args[0] + " :Cannot join channel (+l)"; break ;
			case ERR_UNKNOWNMODE:
				_result += s1 + " :is unknown mode char to me"; break ;
			case ERR_INVITEONLYCHAN:
				_result += _args[0] + " :Cannot join channel (+i)"; break ;
			case ERR_BANNEDFROMCHAN:
				_result += _args[0] + " :Cannot join channel (+b)"; break ;
			case ERR_BADCHANNELKEY:
				_result += _args[0] + " :Cannot join channel (+k)"; break ;
			case ERR_NOPRIVILEGES:
				_result += _args[0] + ":Permission Denied- You're not an IRC operator"; break ;
			case ERR_CHANOPRIVSNEEDED:
				_result += _args[0] + " :You're not channel operator"; break ;
			case ERR_CANTKILLSERVER:
				_result += ":You cant kill a server!"; break ;
			case ERR_NOOPERHOST:
				_result += ":No O-lines for your host"; break ;
			case ERR_UMODEUNKNOWNFLAG:
				_result += ":Unknown MODE FLAG"; break ;
			case ERR_USERSDONTMATCH:
				_result += "Cant change mode for other users"; break ;

			case RPL_NONE:
				_result += ":this is a good place for an easteregg"; break ;
			case RPL_USERHOST:
				_result += s1; break ;
			case RPL_ISON:
				_result += s1; break ;
			case RPL_AWAY:
				_result += _args[0] + " :" + s1; break ;
			case RPL_UNAWAY:
				_result += ":You are no longer marked as being away"; break ;
			case RPL_NOWAWAY:
				_result += ":You have been marked as being away"; break ;
			case RPL_WHOISUSER:
				_result += s1; break ;
			case RPL_WHOISSERVER:
				_result += s1; break ;
			case RPL_WHOISOPERATOR:
				_result += s1 + " :is an IRC operator"; break ;
			case RPL_WHOISIDLE:
				_result += s1 + " :seconds idle"; break ;
			case RPL_ENDOFWHOIS:
				_result += s1 + " :End of /WHOIS list"; break ;
			case RPL_WHOISCHANNELS:
				_result += s1; break ;
			case RPL_WHOWASUSER:
				_result += s1; break ;
			case RPL_ENDOFWHOWAS:
				_result += s1 + " :End of WHOWAS"; break ;
			case RPL_LISTSTART:
				_result += "Channel :Users Name"; break ;
			case RPL_LIST:
				_result += s1; break ;
			case RPL_LISTEND:
				_result += ":End of /LIST"; break ;
			case RPL_CHANNELMODEIS:
				_result += s1; break ;
			case RPL_NOTOPIC:
				_result += _args[0] + " :No topic is set"; break ;
			case RPL_TOPIC:
				_result += _args[0] + " :" + s1; break ;
			case RPL_INVITING:
				_result += _args[1] + " " + _args[0]; break ;
			case RPL_SUMMONING:
				_result += _args[0] + " :Summoning user to IRC"; break ;
			// case RPL_VERSION:
			// 	_result += _server->getVersion(); break ;
			case RPL_WHOREPLY:
				_result += s1; break ;
			case RPL_ENDOFWHO:
				_result += s1 + " :End of /WHO list"; break ;

			case RPL_UMODEIS:
				_result += "+" + _client->getModestr(); break ;
			default:
				_result += "unknown command or not implemented yet. please check Command.cpp";
		}
	}
}
