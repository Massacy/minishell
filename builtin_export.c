/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:01:56 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/09 19:04:37 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_allenv(t_map *env)
{
	t_kv	*cur;

	cur = env->kv_head.next;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else
			printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
}

int	builtin_export(char **argv, t_map *env)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_allenv(env);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (separate_str_to_kv(env, argv[i], true) < 0)
		{
			builtin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}