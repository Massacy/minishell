/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:34:07 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/07 08:31:46 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// char	*ft_strrchr(const char *s, int c)
// {
// 	char	*s_sub;

// 	c %= 256;
// 	if (c < 0)
// 		c += 256;
// 	s_sub = NULL;
// 	while (*s != '\0')
// 	{
// 		if (*s == c)
// 			s_sub = (char *)s;
// 		s++;
// 	}
// 	if (c == '\0')
// 		return ((char *)s);
// 	return (s_sub);
// }

char	*ft_strrchr(const char *s, int c)
{
	char	*s_sub;

	s_sub = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			s_sub = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (s_sub);
}
