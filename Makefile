NAME		= minishell
NAME_LIBFT	= libft/libft.a
CC			= cc
# CFLAGS := -Wall -Wextra -Werror -fsanitize=thread -g
# CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
# INCLUDES := -I/usr/local/include
RLDIR		= $(shell brew --prefix readline)
INCLUDES	= -I include -I$(RLDIR)/include
CFLAGS		= -Wall -Wextra -Werror $(INCLUDES)
LIBS		= -lreadline -L$(RLDIR)/lib
SRCS		= minishell.c tokenizer.c expand.c parse.c signal.c builtin.c environment.c
OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)
	@echo 'set echo-control-characters off' > ~/.inputrc
	@touch .minishell_rc

$(NAME_LIBFT):
	make -C libft

$(NAME) : $(OBJS) $(NAME_LIBFT)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(NAME_LIBFT) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS) ~/.inputrc
	make -C libft clean
	@rm .minishell_rc

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean all

.PHONY: clean fclean re all