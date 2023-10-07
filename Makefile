NAME		= minishell
NAME_LIBFT	= libft/libft.a
NAME_GNL	= gnl/get_next_line
CC			= cc
# CFLAGS := -Wall -Wextra -Werror -fsanitize=thread -g
# CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
# INCLUDES := -I/usr/local/include
RLDIR		= $(shell brew --prefix readline)
INCLUDES	= -I include -I$(RLDIR)/include
CFLAGS		= -Wall -Wextra -Werror $(INCLUDES)
LIBS		= -lreadline -L$(RLDIR)/lib
SRCS		= minishell.c tokenizer.c expand.c parse.c signal.c environment.c\
			  bltin_cd.c bltin_export.c bltin_unset.c bltin_env.c bltin_exit.c
OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)
	@echo 'set echo-control-characters off' > ~/.inputrc
	@rm -f ~/.minishell_rc
	@touch ~/.minishell_rc
	@chmod 666 ~/.minishell_rc

$(NAME_LIBFT):
	make -C libft

$(NAME_GNL):
	make -C gnl

$(NAME) : $(OBJS) $(NAME_LIBFT) $(NAME_GNL)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(NAME_LIBFT) $(NAME_GNL) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS) ~/.inputrc ~/.minishell_rc
	make -C libft clean
	make -C gnl clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean
	make -C gnl clean

re : fclean all

.PHONY: clean fclean re all