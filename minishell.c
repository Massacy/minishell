/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/08/28 14:57:58 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int free_split(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

int main(int argc, char const *argv[])
{
	char *prompt;
	char **split;

	(void)argc;
	(void)argv;
	prompt = NULL;
	while (1)
	{
		prompt = readline("$> ");
		if (prompt == NULL)
			break;
		if (ft_strlen(prompt) == 0)
			continue;
		split = ft_split(prompt, ' ');
		add_history(prompt);
		if (ft_strlen(prompt) == 4 && ft_strncmp(prompt, "exit", 4) == 0)
		{
			free(prompt);
			free_split(split);
			break;
		}
		else if (ft_strlen(split[0]) == 4 && ft_strncmp(split[0], "echo", 4) == 0)
		{
			if (split[1] == NULL)
				printf("\n");
			else if (ft_strlen(split[1]) == 2 && ft_strncmp(split[1],"-n", 2) == 0)
				if (split[2] == NULL)
					printf("");
				else
					printf("%s", &prompt[7]);
			else
				printf("%s\n", &prompt[5]);
		}
		else
			printf("builtin not found: %s\n", prompt);
		free(prompt);
		free_split(split);
	}
	printf("bye~!\n");
	return 0;
}
