# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiyu <smiyu@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 22:22:44 by smiyu             #+#    #+#              #
#    Updated: 2023/10/06 16:21:31 by smiyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

SRCS	=	get_next_line.c get_next_line_utils.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra -D BUFFER_SIZE=42

NAME	=	get_next_line

$(NAME): $(OBJS)
	ar crs $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re