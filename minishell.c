/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/08/28 06:01:02 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const *argv[])
{
	char *prompt;

	(void)argc;
	(void)argv;
	prompt = NULL;
	while (1)
	{
		prompt = readline("$> ");
		if (prompt == NULL)
			break;
		if (ft_strncmp(prompt, "exit", 4) == 0)
			break;
		printf("%s\n", prompt);
		free(prompt);
	}
	printf("exit\n");
	return 0;
}
