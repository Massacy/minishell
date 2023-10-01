/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:46:06 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/01 17:46:08 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ND_SIMPLE_CMD,
};
typedef enum e_node_kind	t_node_kind;

typedef struct s_node		t_node;
typedef struct s_node
{
	t_token					*args;
	t_node_kind				kind;
	t_node					*next;
}							t_node;
