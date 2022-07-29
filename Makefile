NAME		=	ircserv

SRCF		=	sources
SRCF_B		=	$(SRCF)/bonus
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
				client/cmds/channel \
				client/cmds/connection \
				client/cmds/misc \
				client/cmds/optional \
				client/cmds/queries \
				client/cmds/server \
				client/cmds/smesg \
				util \
				debug

FIL_B		=

SRCS_M		=	$(addsuffix .cpp, $(addprefix $(SRCF)/, $(FIL_M)))
SRCS_B		=	$(addsuffix _bonus.cpp, $(addprefix $(SRCF_B)/, $(FIL_M) $(FIL_B)))

OBJS_M		=	$(SRCS_M:.cpp=.o)
OBJS_B		=	$(SRCS_B:.cpp=.o)

# INC			=	$(foreach d, $(INCF), -I$d)

CC			=	c++
CFLAGS		=	-I$(INCF) -O3 -Wall -Wextra -std=c++98 -pedantic # Werror omitted for now.

RM			=	rm -f

%.o			:	%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(OBJS_M)
			$(CC) $(OBJS_M) $(CFLAGS) $(CFLAG_EXT) -o $(NAME)

bonus		:	$(OBJS_B)
			$(CC) $(OBJS_B) $(CFLAGS) $(CFLAG_EXT) -o $(NAME)

clean		:
			$(RM) $(OBJS_M) $(OBJS_B)

all			:	$(NAME)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean all


.PHONY		:	.c.o all clean fclean re bonus
