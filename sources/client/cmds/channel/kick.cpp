#include "channel.hpp"


/*
	Command: KICK
	Parameters: <channel> <user> [<comment>]
	Example:
		KICK &Melbourne Matthew
			; &Melbourne의 킥 매튜
		KICK #Finnish John :Speaking English
			; "영어 말하기"를 이유(댓글)로 사용하여 #Finnish에서 John을 걷어차십시오.
		:WiZ KICK #Finnish John
			; 채널 #Finnish에서 John을 제거하라는 WiZ의 KICK 메시지
	Numeric Replies:
		ERR_NEEDMOREPARAMS
		ERR_NOSUCHCHANNEL
		ERR_BADCHANMASK
		ERR_CHANOPRIVSNEEDED
		ERR_NOTONCHANNEL
*/
/*
ERR_NEEDMOREPARAMS
	"<command> :Not enough parameters"
ERR_NOSUCHCHANNEL
	"<channel name> :No such channel"
ERR_BADCHANMASK
	"<channel> :Bad Channel Mask"
ERR_CHANOPRIVSNEEDED
	"<channel> :You're not channel operator"
ERR_NOTONCHANNEL
	"<channel> :You're not on that channel"
*/
// argc : 2
// args[0] : 채널명
// args[1] : nickname
void	irc::cmd::kick(Command* cmd)
{
	std::string	msg;

	// std::cout << cmd->getArgC() << " " << cmd->getArgs()[0] << " " << cmd->getArgs()[1] << std::endl;
	// if (!cmd->getArgs()[2].empty())
	// 	std::cout << cmd->getArgs()[2] << std::endl;

	if (cmd->getArgC() != 2 && cmd->getArgC() != 3)
	{
		cmd->queue(ERR_NEEDMOREPARAMS);
		return ;
	}



	// (void)cmd;
}
