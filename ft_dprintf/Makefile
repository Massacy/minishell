CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_dprintf.c utils/ft_strlen.c utils/ft_itoa.c utils/ft_dutils1.c utils/ft_dutils2.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
NAME = dprintf.a

$(NAME): $(OBJS)
	ar r $(NAME) $(OBJS)
# $(CC) $(CFLAGS) $(OBJS) -o $(NAME)
all: $(NAME)
clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean $(NAME)

.PHONY: clean fclean re all