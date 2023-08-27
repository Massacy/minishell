/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 07:01:32 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/30 17:00:11 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	cnt;

	cnt = 0;
	while (src[cnt] != '\0')
		cnt++;
	if (size == 0)
		return (cnt);
	i = 0;
	while (i < size - 1 && i < cnt)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (cnt);
}
