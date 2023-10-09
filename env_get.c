/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:59:59 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/09 06:36:54 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_kv_value(t_map *map, char *key)
{
	t_kv	*cur;

	if (key == NULL)
		return (NULL);
	cur = map->kv_head.next;
	while (cur != NULL)
	{
		if (ft_strlen(cur->key) == ft_strlen(key)
			&& ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

char	*get_key_value_string(t_kv *kv)
{
	size_t	strsize;
	char	*s;

	strsize = ft_strlen(kv->key) + 2;
	if (kv->value)
		strsize += ft_strlen(kv->value);
	s = malloc(strsize);
	if (s == NULL)
		fatal_error("malloc");
	strlcpy(s, kv->key, strsize);
	if (kv->value)
	{
		strlcat(s, "=", strsize);
		strlcat(s, kv->value, strsize);
	}
	return (s);
}

size_t	map_len(t_map *map, bool count_null_value)
{
	size_t	len;
	t_kv	*kv;

	len = 0;
	kv = map->kv_head.next;
	while (kv != NULL)
	{
		if (kv->value || count_null_value)
			len++;
		kv = kv->next;
	}
	return (len);
}

char	**get_environ(t_map *map)
{
	size_t	i;
	size_t	size;
	t_kv	*kv;
	char	**env;

	size = map_len(map, false) + 1;
	env = ft_calloc(size, sizeof(char *));
	i = 0;
	kv = map->kv_head.next;
	while (kv)
	{
		if (kv->value)
		{
			env[i] = get_key_value_string(kv);
			i++;
		}
		kv = kv->next;
	}
	env[i] = NULL;
	return (env);
}
