/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:27:30 by imasayos          #+#    #+#             */
/*   Updated: 2023/09/23 18:19:30 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

#define SINGLE_QUOTE_CHAR '\''

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
void fatal_error(const char *msg);
void expand(t_token *tok);
char *search_path(const char *filename);

#endif