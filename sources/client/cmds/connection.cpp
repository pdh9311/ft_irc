#include "cmds.hpp"

/*
  4.1.1 Password message ...................................   14
         4.1.2 Nickname message ...................................   14
         4.1.3 User message .......................................   15
         4.1.4 Server message .....................................   16
         4.1.5 Operator message ...................................   17
         4.1.6 Quit message .......................................   17
         4.1.7 Server Quit message ...........
		 */


#include <iostream>

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