/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 02:14:05 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/01 20:49:30 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	count_word(char const *s, char c)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || (i > 0 && s[i - 1] == c)) && s[i] != c)
			cnt++;
		i++;
	}
	return (cnt);
}

static char	*ft_word_cpy(char const *s, char c, char const **s_sub)
{
	char	*ptr_sub;
	size_t	cnt_alpha;

	cnt_alpha = 0;
	while (*s == c)
		s++;
	while (s[cnt_alpha] != c && s[cnt_alpha] != '\0')
		cnt_alpha++;
	ptr_sub = malloc(cnt_alpha + 1);
	if (ptr_sub == NULL)
		return (NULL);
	ft_strlcpy(ptr_sub, s, cnt_alpha + 1);
	while (cnt_alpha--)
		s++;
	*s_sub = s;
	return (ptr_sub);
}

static void	*ft_free_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	cnt_word;
	size_t	i;
	char	**ptr1;
	char	*ptr_sub;

	if (s == NULL)
		return (NULL);
	cnt_word = count_word(s, c);
	ptr1 = malloc(sizeof(char *) * (cnt_word + 1));
	if (ptr1 == NULL)
		return (NULL);
	i = 0;
	while (i < cnt_word)
	{
		ptr_sub = ft_word_cpy(s, c, &s);
		if (ptr_sub == NULL)
			return (ft_free_split(ptr1));
		ptr1[i++] = ptr_sub;
	}
	ptr1[i] = NULL;
	return (ptr1);
}
