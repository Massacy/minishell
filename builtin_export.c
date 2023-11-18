/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:01:56 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/12 17:22:34 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*copy_map(t_map *env)
{
	t_map	*cpy_map;
	t_kv	*cur;

	cpy_map = new_map();
	cur = env->kv_head.next;
	while (cur)
	{
		set_kv_in_map(cpy_map, cur->key, cur->value);
		cur = cur->next;
	}
	return (cpy_map);
}

t_map	*sort_map(t_map *env)
{
	t_map	*cpy_map;
	t_map	*sort_map;
	t_kv	*cur;
	t_kv	*max;

	cpy_map = copy_map(env);
	sort_map = new_map();
	cur = cpy_map->kv_head.next;
	while (cur)
	{
		max = cur;
		while (cur)
		{
			if (ft_strcmp(max->key, cur->key) < 0)
				max = cur;
			cur = cur->next;
		}
		set_kv_in_map(sort_map, max->key, max->value);
		unset_kv_in_map(cpy_map, max->key);
		cur = cpy_map->kv_head.next;
	}
	free_map(cpy_map);
	return (sort_map);
}

void	print_allenv(t_map *env)
{
	t_map	*s_map;
	t_kv	*cur;

	s_map = sort_map(env);
	cur = s_map->kv_head.next;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else
			printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
	free_map(s_map);
}

int	builtin_export(char **argv, t_map *env)
{
	int		status;
	size_t	i;

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
