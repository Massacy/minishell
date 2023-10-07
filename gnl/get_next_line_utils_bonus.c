/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiyu <smiyu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:06:31 by smiyu             #+#    #+#             */
/*   Updated: 2023/10/06 23:24:32 by smiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s ++;
	}
	if (!c)
		return ((char *)s);
	return (NULL);
}

size_t	gnl_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i] != 0)
	{
		dest[i] = src[i];
		i ++;
	}
	if (dstsize)
		dest[i] = '\0';
	return (gnl_strlen(src));
}

char	*gnl_strdup(char *s)
{
	char	*result;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len ++;
	result = (char *)malloc(s_len + 1);
	gnl_strlcpy(result, s, s_len + 1);
	return (result);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strdup((char *)s2));
	if (!s2)
		return (gnl_strdup((char *)s1));
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	gnl_strlcpy(result, s1, s1_len + s2_len + 1);
	gnl_strlcpy(result + s1_len, s2, s2_len + 1);
	return (result);
}
