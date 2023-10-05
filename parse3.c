/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 05:06:00 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/06 06:31:17 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

/*
	tokの末尾にelemを追加する。
*/
void	append_tok(t_token **tok, t_token *elem)
{
	if (*tok == NULL)
	{
		*tok = elem;
		return ;
	}
	append_tok(&(*tok)->next, elem);
}

void	append_node(t_node **node, t_node *elem)
{
	if (*node == NULL)
	{
		*node = elem;
		return ;
	}
	append_node(&(*node)->next, elem);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = ft_strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}
