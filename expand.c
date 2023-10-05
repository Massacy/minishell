/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 05:00:58 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/06 05:35:34 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

// void	expand_variable(t_node *node)
// {
// 	if (node == NULL)
// 		return ;
// 	expand_variable_tok(node->args);
// 	expand_variable_tok(node->filename);
// 	expand_variable(node->redirects);
// 	expand_variable(node->command);
// 	expand_variable(node->next);
// }

// void	expand(t_node *node)
// {
// 	// expand_variable(node);
// 	expand_quote_removal(node);
// }

void	expand(t_node *node)
{
	expand_quote_removal(node);
}
