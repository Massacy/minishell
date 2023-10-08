/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/08 19:31:08 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t g_sig;

// 子プロセスで*lineに入っているコマンドを実行する。
void	interpret(char *line, int *stat_loc)
{
	t_token	*tok;
	t_node	*node;
	bool	syntax_error;

	syntax_error = false;
	tok = tokenize(line, &syntax_error);
	if (at_eof(tok))
		;
	else if (syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok, &syntax_error);
		if (syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			expand(node, stat_loc);
			*stat_loc = exec(node);
		}
		free_node(node);
	}
	free_tok(tok);
}

// __attribute__((destructor))
// static void destructor() {
//     // system("leaks -q a.out");
//     system("leaks -q minishell");
// }

int	main(void)
{
	char	*prompt;
	int		exit_status;

	prompt = NULL;
	setup_signal();
	exit_status = 0;
	while (1)
	{
		prompt = readline("$> ");
		if (prompt == NULL)
			break ;
		if (ft_strlen(prompt) == 0)
			continue ;
		add_history(prompt);
		interpret(prompt, &exit_status);
		free(prompt);
	}
	exit(exit_status);
}
