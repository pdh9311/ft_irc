#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <string>
#include <vector>
#include <set>

#include <unistd.h>

namespace irc
{
	class Channel;
	class Server;
	class Command;

	class Client
	{
		friend class Server;

		public:
			typedef std::set<char>	mode_t;
			enum client_stats
			{
				PENDING,	// tcp/ip connection accepted
				AUTH,		// password accepted
				LOGGEDIN,	// USER command accepted, live client
				DISCONNECT	// client disconnected, pending for destruction
			};

		private:
			const int		_fd;
			Server*			_server;
			Channel*		_cchannel;
			time_t			_last_ping;
			char			_status;
			std::string		_buf;
			std::string		_nick;
			std::string		_user_name;
			std::string		_real_name;
			std::string		_last_nick;
			std::string		_away_msg;
			mode_t			_modes;

			int		parse();

		public:
			Client (const int& fd, Server* server);
			virtual	~Client();

			void	recv();
			void	queue(std::string msg) const;

			char				getStatus() const;
			const int&			getFD() const;
			const time_t&		getLastPing() const;
			const std::string&	getNick() const;
			const std::string&	getUserName() const;
			const std::string&	getRealName() const;
			const mode_t&		getModes() const;
			const std::string	getModestr() const;
			const Channel*		getCChannel() const;
			bool				hasMode(char c) const;
			bool				isLoggedIn() const;
			const std::string&	getAwayMsg() const;

			void	setAwayMsg(const std::string& msg);
			void	setLastPing(const time_t& time);
			void	setNick(const std::string& str);
			void	setUserName(const std::string& name);
			void	setRealName(const std::string& name);
			void	setModes(const std::string& modes);
			void	setMode(const char c);
			void	unsetModes(const std::string& modes);
			void	unsetMode(const char c);
			void	setCChannel(Channel* channel);
			void	setStatus(const char status);
	};
}

#endif
