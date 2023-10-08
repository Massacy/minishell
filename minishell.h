/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:27:30 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/08 19:48:47 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_dprintf/ft_dprintf.h"
# include "libft/libft.h"
# include "structure.h"
# include <stdio.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
#include <sys/ioctl.h>

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define ERROR_PREFIX "\u2757"
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define PATH_MAX 1024

t_token	*tokenize(char *line, bool *syntax_error);

// minishell.c

// exec.c
int		exec(t_node *node);
char	*search_path(const char *filename);

// exec_sub.c
void	validate_access(const char *path, const char *filename);
char	*accessible_path(char *path);
char	**token_list_to_argv(t_token *tok);

// expand.c
void	expand(t_node *node, int *last_status);

// expand_variable_sub.c
void	append_num(char **dst, unsigned int num);

// expand_variable_param.c
void	expand_special_parameter_str(char **dst, char **rest, char *p,
			int *last_status);
bool	is_special_parameter(char *s);

// tokenizer.c
bool	is_metacharacter(char c);
t_token	*new_token(char *word, t_token_kind kind);
bool	startswith(const char *s, const char *keyword);

// tokenizer2.c
bool	is_blank(char c);
bool	is_word(const char *s);

// error.c
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	todo(const char *msg) __attribute__((noreturn));

// error2.c
void	err_exit(const char *location, const char *msg,
			int status) __attribute__((noreturn));
void	parse_error(const char *location, t_token **rest, t_token *tok,
			bool *syntax_error);
void	tokenize_error(const char *location, char **rest, char *line,
			bool *syntax_error);
void	perror_prefix(void);
void	xperror(const char *location);

// parse.c
bool	at_eof(t_token *tok);
t_node	*parse(t_token *tok, bool *syntax_error);
void	append_cmd_elem(t_node *cmd, t_token **rest, t_token *tok,
			bool *syntax_error);
t_node	*simple_command(t_token **rest, t_token *tok, bool *syntax_error);

// parse.c
t_node	*parse_pipeline(t_token **rest, t_token *tok, bool *syntax_error);
t_node	*redirect_ioah(t_token **rest, t_token *tok, t_node_kind kind,
			int target_fd);

// parse2.c
bool	is_word_tok(t_token *tok);
bool	is_control_operator(t_token *tok);
bool	equal_op(t_token *tok, char *op);

//parse3.c
t_node	*new_node(t_node_kind kind);
void	append_tok(t_token **tok, t_token *elem);
void	append_node(t_node **node, t_node *elem);
t_token	*tokdup(t_token *tok);

// redirection.c
int		open_redirect_file(t_node *node);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);

// destructor.c
void	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

// pipe.c
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

// expand.c
void	expand_quote_removal(t_node *node);

// expand2.c
void	append_char(char **s, char c);

// expand_variable.c
void	expand_variable(t_node *node, int *last_status);

// expand_variable_sub.c
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_variable(char *s);
bool	is_special_parameter(char *s);
void	expand_special_parameter_str(char **dst, char **rest, \
			char *p, int *last_status);

// ft_strndup.c
char	*ft_strndup(const char *s1, size_t n);

// exec_sub.c
char	*accessible_path(char *path);
void	validate_access(const char *path, const char *filename);
char	**token_list_to_argv(t_token *tok);

// signal.h

void	setup_signal(void);
void	reset_signal(void);

#endif
