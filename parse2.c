/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 05:06:00 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/23 15:42:48 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	if (ft_strlen(tok->word) != ft_strlen(op))
		return (false);
	return (ft_strncmp(tok->word, op, ft_strlen(op)) == 0);
}

bool	is_word_tok(t_token *tok)
{
	return (tok->kind == TK_WORD);
}

bool	is_control_operator(t_token *tok)
{
	size_t				i;
	static char *const	operators[] = {"|", "\n"};

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
}
