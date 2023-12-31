/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 06:10:55 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/22 04:16:24 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_node *node, t_es *es)
{
	int		status;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (ft_strlen(argv[0]) == 4 && ft_strncmp(argv[0], "exit", 4) == 0)
		status = builtin_exit(argv, es->last_status);
	else if (ft_strlen(argv[0]) == 6 && ft_strncmp(argv[0], "export", 6) == 0)
		status = builtin_export(argv, es->env);
	else if (ft_strlen(argv[0]) == 5 && ft_strncmp(argv[0], "unset", 5) == 0)
		status = builtin_unset(argv, es->env);
	else if (ft_strlen(argv[0]) == 3 && ft_strncmp(argv[0], "env", 3) == 0)
		status = builtin_env(es->env);
	else if (ft_strlen(argv[0]) == 2 && ft_strncmp(argv[0], "cd", 2) == 0)
		status = builtin_cd(argv, es->env);
	else if (ft_strlen(argv[0]) == 3 && ft_strncmp(argv[0], "pwd", 3) == 0)
		status = builtin_pwd();
	else if (ft_strlen(argv[0]) == 4 && ft_strncmp(argv[0], "echo", 4) == 0)
		status = builtin_echo(argv);
	else
		todo("exec_builtin");
	free_argv(argv);
	return (status);
}

const char	*g_builtin_commands[] = {"exit", "export", "unset", "env", "cd", \
	"pwd", "echo"};

bool	is_builtin(t_node *node)
{
	const char		*cmd_name;
	unsigned int	i;

	if (node == NULL || node->command == NULL | node->command->args == NULL \
		||node->command->args->word == NULL)
		return (false);
	cmd_name = node->command->args->word;
	i = 0;
	while (i < sizeof(g_builtin_commands) / sizeof(*g_builtin_commands))
	{
		if (ft_strlen(cmd_name) == ft_strlen(g_builtin_commands[i]) \
			&& ft_strncmp(cmd_name, g_builtin_commands[i], \
			ft_strlen(cmd_name)) == 0)
			return (true);
		i++;
	}
	return (false);
}
