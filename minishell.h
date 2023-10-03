/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:27:30 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/04 06:35:27 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_dprintf/ft_dprintf.h"
# include "structure.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define ERROR_PREFIX "\u2757"
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define PATH_MAX 1024

t_token *tokenize(char *line, bool *syntax_error);

// minishell.c
void	fatal_error(const char *msg);
void	expand(t_node *node);
char	*search_path(const char *filename);
void	validate_access(const char *path, const char *filename);

// tokenizer.c
bool	is_metacharacter(char c);
t_token	*new_token(char *word, t_token_kind kind);
bool startswith(const char *s, const char *keyword);

// error.c
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	todo(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg,
			int status) __attribute__((noreturn));
void	parse_error(const char *location, t_token **rest, t_token *tok,
			bool *syntax_error);
void	tokenize_error(const char *location, char **rest, char *line,
			bool *syntax_error);
void	xperror(const char *location);

// parse.c
bool	at_eof(t_token *tok);
t_node *parse(t_token *tok, bool *syntax_error);
void append_cmd_elem(t_node *cmd, t_token **rest, t_token *tok, bool *syntax_error);
t_node *simple_command(t_token **rest, t_token *tok, bool *syntax_error);

// redirection.c
int		open_redirect_file(t_node *node);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);

// destructor.c
void 	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

// pipe.c
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

#endif