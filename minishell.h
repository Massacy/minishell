#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'

typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
}						t_token_kind;

// `word` is zero terminated string.
typedef struct s_token	t_token;
typedef struct s_token
{
	char				*word;
	t_token_kind		kind;
	t_token				*next;
}						t_token;

# define PATH_MAX 1024

t_token					*tokenize(char *line);

// minishell.c
void					fatal_error(const char *msg);
void					expand(t_token *tok);
char					*search_path(const char *filename);

// tokenizer.c
bool					is_metacharacter(char c);
t_token *new_token(char *word, t_token_kind kind);

// signal.c
void	set_signal();
void	signal_handler(int sig);

// builtin.c
void	minishell_cd(char *dir);
// void	minishell_pwd();
void	minishell_export(char **argv);
void	minishell_unset(char **argv);
// void	minishell_env(char **argv);
void	minishell_exit(int exit_status);

// environment.c
void	env_init(char **envp);
void	env_translate(char **argv);

#endif