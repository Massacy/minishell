/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:00:43 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 22:37:36 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_start_index(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	flg;

	j = 0;
	while (s1[j] != '\0')
	{
		flg = 0;
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[j] == set[i])
			{
				flg = 1;
				break ;
			}
			i++;
		}
		if (flg != 1)
			return (j);
		j++;
	}
	return (j);
}

int	get_end_index(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	flg;

	j = ft_strlen(s1) - 1;
	while (j >= 0)
	{
		flg = 0;
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[j] == set[i])
			{
				flg = 1;
				break ;
			}
			i++;
		}
		if (flg != 1)
			return (j);
		j--;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		trim_len;
	char	*ptr;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = get_start_index(s1, set);
	end = get_end_index(s1, set);
	trim_len = end - start + 1;
	if (trim_len <= 0)
		trim_len = 0;
	ptr = malloc(trim_len + 1);
	if (ptr != NULL)
	{
		i = 0;
		while (i < trim_len)
		{
			ptr[i] = s1[i + start];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
