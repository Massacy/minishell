/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:51:32 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/23 15:11:10 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_map *env)
{
	t_kv	*cur;

	cur = env->kv_head.next;
	while (cur != NULL)
	{
		if (cur->value == NULL)
			printf("%s=\n", cur->key);
		else
			printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (0);
}
