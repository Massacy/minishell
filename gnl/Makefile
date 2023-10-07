# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiyu <smiyu@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 22:22:44 by smiyu             #+#    #+#              #
#    Updated: 2022/10/14 17:27:02 by smiyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

SRCS	=	get_next_line.c get_next_line_utils.c

OBJS	=	$(SRCS:.c=.o)

B_SRCS	=	get_next_line_bonus.c get_next_line_utils_bonus.c
# B_SRCS	=	$(SRCS:.c=_bonus.c)

B_OBJS	=	$(B_SRCS:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra -D BUFFER_SIZE=42

NAME	=	get_next_line

ifdef WITH_BONUS
SRCS	=	$(B_SRCS)
OBJS	=	$(B_OBJS)
endif

$(NAME): $(OBJS)
	ar crs $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	make WITH_BONUS=1

.PHONY: all clean fclean re bonus