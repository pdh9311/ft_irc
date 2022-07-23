# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 23:04:25 by minsunki          #+#    #+#              #
#    Updated: 2022/07/23 22:00:23 by minsunki         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_irc

SRCF		=	sources
SRCF_B		=	$(SRCF)/bonus
INCF		=	sources

FIL_M		=	main \
				server/Server \
				client/Client \
				client/Command \
				client/cmds/connection \
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
