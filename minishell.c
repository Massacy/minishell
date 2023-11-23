/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/23 19:02:25 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

void	interpret(char *line, t_es *es)
{
	t_token	*tok;
	t_node	*node;
	bool	syntax_error;

	syntax_error = false;
	tok = tokenize(line, &syntax_error);
	if (at_eof(tok))
		;
	else if (syntax_error)
		*es->last_status = ERROR_TOKENIZE;
	else
	{
		node = parse(tok, &syntax_error);
		if (syntax_error)
			*es->last_status = ERROR_PARSE;
		else
		{
			expand(node, es);
			*es->last_status = exec(node, es);
		}
		free_node(node);
	}
	free_tok(tok);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

int	main(void)
{
	char	*prompt;
	int		exit_status;
	t_es	es;

	rl_outstream = stderr;
	prompt = NULL;
	es.env = init_default_env_in_map();
	es.last_status = &exit_status;
	exit_status = 0;
	while (1)
	{
		g_sig = 0;
		setup_signals();
		prompt = readline("$> ");
		if (prompt == NULL)
			break ;
		if (ft_strlen(prompt) != 0)
		{
			add_history(prompt);
			interpret(prompt, &es);
		}
		free(prompt);
	}
	exit(exit_status);
}
