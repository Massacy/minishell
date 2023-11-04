/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:30:47 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/04 16:54:37 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

t_map	*init_default_env_in_map(void)
{
	extern char	**environ;
	t_map		*map;
	int			i;

	map = new_map();
	i = 0;
	while (environ[i])
	{
		separate_str_to_kv(map, environ[i], false);
		i++;
	}
	return (map);
}

t_map	*new_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		fatal_error("calloc");
	return (map);
}

t_kv	*new_kv(char *key, char *value)
{
	t_kv	*kv;

	kv = ft_calloc(1, sizeof(t_kv));
	if (kv == NULL)
		fatal_error("calloc");
	kv->key = key;
	kv->value = value;
	return (kv);
}

void	free_3ptrs(void *ptr1, void *ptr2, void *ptr3)
{
	free(ptr1);
	free(ptr2);
	free(ptr3);
}
