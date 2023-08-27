NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror

# OUTDIR = objs
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
 ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
 ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_BONUS := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
ifdef BONUS_FLAG
	SRCS = $(SRCS_BONUS)
endif
OBJS := $(patsubst %.c, %.o, $(SRCS))
OBJS_BONUS := $(patsubst %.c, %.o, $(SRCS_BONUS))
# 注意 : make とmake bonusしたときにlibft.aがどちらか最後のコマンドのアーカイブファイルになっている。再makeしてもis up to dateになるのでfcleanしてから再makeすること。

# OBJS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o 
# OBJS = $(addprefix ./$(OUTDIR)/, $(patsubst %.c, %.o, $(SRCS)))

# objs/%.o:srcs/%.c (ディレクトリ分けたいとき。objsとかsrcsとかは適宜変更)
# %.c:%.o
# 	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar r $(NAME) $(OBJS)
# $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus :
	@$(MAKE) BONUS_FLAG=1

all : $(NAME)
clean :
	rm -f $(OBJS) $(OBJS_BONUS)
fclean : clean
	rm -f $(NAME)
re : fclean $(NAME)

norm:
	norminette -R CheckForbiddenSourceHeader ${file}

norma :
	norminette -R CheckForbiddenSourceHeader $(SRCS)

.PHONY: clean fclean re all norm norma
