/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:46:06 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/09 20:51:11 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
}							t_token_kind;

// `word` is zero terminated string.
typedef struct s_token		t_token;
typedef struct s_token
{
	char					*word;
	t_token_kind			kind;
	t_token					*next;
}							t_token;

enum						e_node_kind
{
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
};
typedef enum e_node_kind	t_node_kind;

typedef struct s_node		t_node;
typedef struct s_node
{
	t_node_kind				kind;
	t_node					*next;

	t_token					*args;
	t_node					*redirects;

	int						target_fd;
	t_token					*filename;
	t_token					*heredoc;
	int						file_fd;
	int						target_fd_copy;

	int						inpipe[2];
	int						outpipe[2];
	t_node					*command;
}							t_node;

typedef struct s_keyvalue
{
	char					*key;
	char					*value;
	struct s_keyvalue		*next;
}							t_kv;

typedef struct s_map
{
	t_kv					kv_head;
}							t_map;

typedef struct s_env_and_status
{
	t_map	*env;
	int 	*last_status;
}			t_es;

#endif
