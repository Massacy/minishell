NAME := minishell
NAME_LIBFT := libft/libft.a
NAME_FT_DPRINTF := ft_dprintf/dprintf.a
CC := cc
RLDIR    = $(shell brew --prefix readline)
INCLUDES = -I include -I$(RLDIR)/include
LIBS     = -lreadline -L$(RLDIR)/lib
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
CFLAGS += -fsanitize=address -g
# CFLAGS := -Wall -Wextra -Werror -fsanitize=thread -g
# CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
# INCLUDES := -I/usr/local/include
# INCLUDES := -lreadline
SRCS := minishell.c tokenizer.c expand.c parse.c error.c destructor.c redirection.c pipe.c \
 error2.c expand2.c parse2.c redirection2.c parse3.c ft_strndup.c tokenizer2.c \
 expand_variable.c expand_variable_sub.c expand_variable_param.c exec.c exec_sub.c \
 signal.c env_init.c env_set.c env_get.c \
 builtin.c builtin_exit.c builtin_export.c builtin_unset.c \
 builtin_env.c

OBJS := $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)
	@echo 'set echo-control-characters off' > ~/.inputrc

$(NAME_FT_DPRINTF):
	make -C ft_dprintf

$(NAME_LIBFT):
	make -C libft

$(NAME) : $(OBJS) $(NAME_FT_DPRINTF) $(NAME_LIBFT)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(NAME_FT_DPRINTF) $(NAME_LIBFT) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	make -C libft clean
	make -C ft_dprintf clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean
	make -C ft_dprintf fclean

re : fclean 
	make $(NAME)

.PHONY: clean fclean re all