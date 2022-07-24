#include "cmds.hpp"
#include "client/Command.hpp"
#include "client/Client.hpp"
#include "server/Server.hpp"

namespace irc
{
	namespace cmd
	{
		void	nick(Command* cmd)
		{
			std::cout << "nick command called" << std::endl;
			std::cout << "prefix:" << cmd->getPrefix() << std::endl;
			std::cout << "command:" << cmd->getCommand() << std::endl;
			std::vector<std::string>	args = cmd->getArgs();
			for(int i = 0; i < args.size(); ++i)
				std::cout << "arg#" << i << ":" << args[i] << std::endl;
		}
		
		void	user(Command* cmd)
		{
			std::cout << "user command called" << std::endl;
			std::cout << "result will be set to 001 (RPL_WELCOME) for now" << std::endl;
			std::string	ret = ":localhost 001 " + cmd->getClient()->getNick();
			cmd->setResult(ret);
		}
		
		void	server(Command* cmd)
		{
			
		}
		
		void	oper(Command* cmd)
		{
			
		}
		
		void	quit(Command* cmd)
		{
			
		}
		
		void	squit(Command* cmd)
		{
			
		}
	}
}