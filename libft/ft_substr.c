/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:43:34 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 22:57:04 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr != NULL)
	{
		i = 0;
		while (i < len && *s != '\0' && start < s_len)
		{
			ptr[i] = s[i + start];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
