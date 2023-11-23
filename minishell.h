/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:27:30 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/23 18:29:07 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_dprintf/ft_dprintf.h"
# include "libft/libft.h"
# include "structure.h"
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define ERROR_PREFIX "\u2757"
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define PATH_MAX 1024
# define LOOP_END 10
# define LOOP_CONTINUE 11

t_token	*tokenize(char *line, bool *syntax_error);

// minishell.c

// exec.c
int		exec(t_node *node, t_es *es);
char	*search_path(const char *filename, t_map *env);
int		exec_nonbuiltin(t_node *node, t_map *env) __attribute__((noreturn));

// exec_sub.c
void	validate_access(char *path, char **argv);
char	*accessible_path(char *path);
char	**token_list_to_argv(t_token *tok);

// expand.c
void	expand(t_node *node, t_es *es);

// expand2.c
void	append_char(char **s, char c);
void	expand_quote_removal(t_node *node);

// expand_variable.c
void	expand_variable(t_node *node, t_es *es);

// expand_variable_sub.c
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_variable(char *s);
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
void	builtin_error(const char *func, const char *str, const char *err);
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
void	free_map(t_map *map);

// pipe.c
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

// ft_strndup.c
char	*ft_strndup(const char *s1, size_t n);

// ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

// signal.c
void	handler(int signum);
void	handler2(int signum);
void	setup_signal(int signum, void (*handler)(int));

// signal2.c
void	setup_signals(void);
void	reset_signals(void);
void	setup_signals2(void);

// env_init.c
bool	is_identifier(const char *s);
t_map	*init_default_env_in_map(void);
t_map	*new_map(void);
t_kv	*new_kv(char *key, char *value);
void	free_3ptrs(void *ptr1, void *ptr2, void *ptr3);

// env_set.c
int		separate_str_to_kv(t_map *map, char *str, bool allow_empty_value);
int		set_kv_in_map(t_map *map, char *key, char *value);
int		unset_kv_in_map(t_map *map, const char *key);

// env_get.c
size_t	map_len(t_map *map, bool count_null_value);
char	*get_key_value_string(t_kv *kv);
char	*get_kv_value(t_map *map, char *key);
char	**get_environ(t_map *map);

// builtin.c
bool	is_builtin(t_node *node);
int		exec_builtin(t_node *node, t_es *es);

// builtin_exit.c
int		builtin_exit(char **argv, int *last_status);

// builtin_export.c
int		builtin_export(char **argv, t_map *env);

// builtin_unset.c
int		builtin_unset(char **argv, t_map *env);

// builtin_env.c
int		builtin_env(t_map *env);

// builtin_cd.c
int		builtin_cd(char **argv, t_map *env);

// builtin_pwd.c
int		builtin_pwd(void);

// builtin_echo.c
int		builtin_echo(char **argv);

#endif
