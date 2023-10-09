/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 06:10:55 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/09 14:52:05 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtin(t_node *node, int *last_status)
{
	int		status;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (ft_strlen(argv[0]) == 4 && ft_strncmp(argv[0], "exit", 4) == 0)
		status = builtin_exit(argv, last_status);
	else
		todo("exec_builtin");
	free_argv(argv);
	reset_redirect(node->command->redirects);
	return (status);
}

bool	is_builtin(t_node *node)
{
	const char		*cmd_name;
	char			*builtin_commands[] = {"exit"};
	unsigned int	i;

	if (node == NULL || node->command == NULL || node->command->args == NULL ||
			node->command->args->word == NULL)
		return (false);
	cmd_name = node->command->args->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (ft_strlen(cmd_name) == ft_strlen(builtin_commands[i])
			&& ft_strncmp(cmd_name, builtin_commands[i], ft_strlen(cmd_name)) == 0)
			return (true);
		i++;
	}
	return (false);
}
