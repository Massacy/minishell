NAME := minishell
NAME_LIBFT := libft/libft.a
NAME_FT_DPRINTF := ft_dprintf/dprintf.a
CC := cc
CFLAGS := -Wall -Wextra -Werror 
# CFLAGS := -Wall -Wextra -Werror -fsanitize=thread -g
# CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
# INCLUDES := -I/usr/local/include
INCLUDES := -lreadline
SRCS := minishell.c tokenizer.c expand.c parse.c error.c destructor.c redirection.c pipe.c
OBJS := $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME_FT_DPRINTF):
	make -C ft_dprintf

$(NAME_LIBFT):
	make -C libft

$(NAME) : $(OBJS) $(NAME_FT_DPRINTF) $(NAME_LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(NAME_FT_DPRINTF) $(NAME_LIBFT) -o $(NAME)

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