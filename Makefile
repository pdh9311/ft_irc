NAME		=	ircserv

SRCF		=	sources
INCF		=	sources

FIL_M		=	main \
				channel/Channel \
				server/Server \
				server/Config \
				server/irc_type/AdministrativeInfo \
				server/irc_type/BounceServer \
				server/irc_type/ClientConnections \
				server/irc_type/ConnectionClasses \
				server/irc_type/DefaultLocalServer \
				server/irc_type/DenyAutoConnections \
				server/irc_type/ExcludedAccounts \
				server/irc_type/ExcludedMachines \
				server/irc_type/HubConnections \
				server/irc_type/LeafConnections \
				server/irc_type/MachineInfo \
				server/irc_type/OperatorPrivileges \
				server/irc_type/PortConnections \
				server/irc_type/RestrictLines \
				server/irc_type/ServerConnections \
				server/irc_type/ServiceConnections \
				server/irc_type/VersionLimitations \
				client/Client \
				client/Command \
				client/cmds/channel/invite \
				client/cmds/channel/join \
				client/cmds/channel/kick \
				client/cmds/channel/list \
				client/cmds/channel/mode \
				client/cmds/channel/names \
				client/cmds/channel/part \
				client/cmds/channel/topic\
				client/cmds/connection/pass \
				client/cmds/connection/nick \
				client/cmds/connection/user \
				client/cmds/connection/server \
				client/cmds/connection/oper \
				client/cmds/connection/quit \
				client/cmds/connection/squit \
				client/cmds/sendmsg/privmsg \
				client/cmds/sendmsg/notice \
				client/cmds/server/motd \
				client/cmds/server/lusers \
				client/cmds/server/version \
				client/cmds/server/stats \
				client/cmds/server/links \
				client/cmds/server/time \
				client/cmds/server/connect \
				client/cmds/server/trace \
				client/cmds/server/admin \
				client/cmds/server/info \
				client/cmds/misc/kill \
				client/cmds/misc/ping \
				client/cmds/misc/pong \
				client/cmds/misc/error \
				client/cmds/queries/who \
				client/cmds/queries/whois \
				client/cmds/queries/whowas \
				client/cmds/optional/away \
				client/cmds/optional/rehash \
				client/cmds/optional/restart \
				client/cmds/optional/summon \
				client/cmds/optional/users \
				client/cmds/optional/wallops \
				client/cmds/optional/userhost \
				client/cmds/optional/ison \
				util \
				debug

SRCS_M		=	$(addsuffix .cpp, $(addprefix $(SRCF)/, $(FIL_M)))

OBJS_M		=	$(SRCS_M:.cpp=.o)

CC			=	c++
CFLAGS		=	-I$(INCF) -O3 -Wall -Wextra -Werror -std=c++98

RM			=	rm -f

%.o			:	%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(OBJS_M)
			$(CC) $(OBJS_M) $(CFLAGS) $(CFLAG_EXT) -o $(NAME)

clean		:
			$(RM) $(OBJS_M)

all			:	$(NAME)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
