/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:26:23 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/07 08:30:03 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// char	*ft_strchr(const char *s, int c)
// {
// 	c %= 256;
// 	if (c < 0)
// 		c += 256;
// 	while (*s != '\0')
// 	{
// 		if (*s == c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if (c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
