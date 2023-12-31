/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:57:57 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/12 17:05:24 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separate_str_to_kv(t_map *map, char *str, bool allow_empty_value)
{
	char	*pos_eq;
	char	*key;
	char	*value;
	int		res;

	pos_eq = ft_strchr(str, '=');
	if (pos_eq == NULL)
	{
		if (!allow_empty_value)
			return (-1);
		key = ft_strdup(str);
		value = NULL;
		if (key == NULL)
			fatal_error("strdup");
	}
	else
	{
		key = ft_strndup(str, pos_eq - str);
		value = ft_strdup(pos_eq + 1);
		if (key == NULL || value == NULL)
			fatal_error("strdup");
	}
	res = set_kv_in_map(map, key, value);
	free_3ptrs(key, value, NULL);
	return (res);
}

static void	update_kv(t_kv *cur, char *value)
{
	free(cur->value);
	if (value == NULL)
		cur->value = NULL;
	else
	{
		cur->value = ft_strdup(value);
		if (cur->value == NULL)
			fatal_error("strdup");
	}
}

// 新しいkvをmap->kv_head.nextにする。
static void	insert_kv(t_map *map, char *key, char *value)
{
	t_kv	*new_cur;

	if (value == NULL)
	{
		new_cur = new_kv(ft_strdup(key), NULL);
		if (new_cur->key == NULL)
			fatal_error("strdup");
	}
	else
	{
		new_cur = new_kv(ft_strdup(key), ft_strdup(value));
		if (new_cur->key == NULL || new_cur->value == NULL)
			fatal_error("strdup");
	}
	new_cur->next = map->kv_head.next;
	map->kv_head.next = new_cur;
}

// 失敗で-1、成功で0を返す。
// elseケースはまだmapにkvが追加されていないとき、またはkeyが存在しないとき。
int	set_kv_in_map(t_map *map, char *key, char *value)
{
	t_kv	*cur;

	if (key == NULL || !is_identifier(key))
		return (-1);
	cur = map->kv_head.next;
	while (cur != NULL)
	{
		if (ft_strlen(cur->key) == ft_strlen(key)
			&& ft_strcmp(cur->key, key) == 0)
			break ;
		cur = cur->next;
	}
	if (cur != NULL)
		update_kv(cur, value);
	else
		insert_kv(map, key, value);
	return (0);
}

int	unset_kv_in_map(t_map *map, const char *key)
{
	t_kv	*cur;
	t_kv	*prev;

	if (key == NULL || !is_identifier(key))
		return (-1);
	prev = &map->kv_head;
	cur = map->kv_head.next;
	while (cur)
	{
		if (ft_strlen(cur->key) == ft_strlen(key)
			&& ft_strcmp(cur->key, key) == 0)
		{
			prev->next = cur->next;
			free_3ptrs(cur->key, cur->value, cur);
			return (0);
		}
		prev = prev->next;
		cur = cur->next;
	}
	return (0);
}
