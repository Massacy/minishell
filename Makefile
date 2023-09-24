NAME := minishell
NAME_LIBFT := libft/libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror 
# CFLAGS := -Wall -Wextra -Werror -fsanitize=thread -g
# CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
# INCLUDES := -I/usr/local/include
INCLUDES := -lreadline
SRCS := minishell.c tokenizer.c expand.c parse.c
OBJS := $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME_LIBFT):
	make -C libft

$(NAME) : $(OBJS) $(NAME_LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(NAME_LIBFT) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	make -C libft clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean 
	make $(NAME)

.PHONY: clean fclean re all