/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 05:33:51 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/06 06:30:43 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup_str;
	size_t	i;

	dup_str = (char *)malloc(sizeof(char) * (n + 1));
	if (dup_str == NULL)
		return (NULL);
	i = 0;
	while (i < n && s1[i] != '\0')
	{
		dup_str[i] = s1[i];
		i++;
	}
	dup_str[i] = '\0';
	return (dup_str);
}
