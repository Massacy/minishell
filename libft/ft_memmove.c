/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 06:02:05 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 16:36:00 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_sub;
	size_t	i;

	dest_sub = dest;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			dest_sub[i] = ((char *)src)[i];
			i++;
		}
	}
	else if (src < dest)
	{
		while (i < n)
		{
			dest_sub[n - i - 1] = ((char *)src)[n - i - 1];
			i++;
		}
	}
	return (dest);
}
