/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 05:00:24 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/12 17:19:50 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	free_tok(node->args);
	free_tok(node->filename);
	free_tok(node->heredoc);
	free_node(node->redirects);
	free_node(node->next);
	free_node(node->command);
	free(node);
}

void	free_tok(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->word)
		free(tok->word);
	free_tok(tok->next);
	free(tok);
}

void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_map(t_map *map)
{
	t_kv	*cur;
	t_kv	*tmp;

	if (map == NULL)
		return ;
	cur = map->kv_head.next;
	while (cur)
	{
		tmp = cur->next;
		free_3ptrs(cur->key, cur->value, cur);
		cur = tmp;
	}
	free(map);
}
