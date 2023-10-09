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
# include <curses.h>

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define RC_PATH "/.minishell_rc"
# define TRC_PATH "/.minishell_trc"
# define PATH_MAX 4096

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

t_token					*tokenize(char *line);

// minishell.c
void					fatal_error(const char *msg);
void					expand(t_token *tok);
char					*search_path(const char *filename);
// int					interpret(t_token *tok);
int						interpret(char **argv);

// tokenizer.c
bool					is_metacharacter(char c);
t_token *new_token(char *word, t_token_kind kind);

// signal.c
void	set_signal();
void	signal_handler(int sig);

// builtin.c
void	minishell_echo(char **argv);
void	minishell_cd(char *dir);
void	minishell_pwd(void);
void	minishell_export(char **argv);
void	minishell_unset(char **argv);
void	minishell_env(char **argv);
void	minishell_exit(int exit_status);

// environment.c
char	*ft_getenv(char *name);
void	env_init(char **envp);
void	env_translate(char **argv);
void	env_loop(char *rc_file, char **argv, void f(char **, char *));

// builtin_export_unset_utils.c
int		check_invalid_identifier(char *s);
void	check_overlap_env_in_argv(char **argv);

#endif