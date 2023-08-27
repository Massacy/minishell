/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:19:27 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 23:00:29 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	size_t	len;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr != NULL)
	{
		i = 0;
		while (i < (int)len)
		{
			ptr[i] = f(i, s[i]);
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
