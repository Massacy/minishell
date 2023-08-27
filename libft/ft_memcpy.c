/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:43:39 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 13:52:44 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_sub;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_sub = dest;
	i = 0;
	while (i < n)
	{
		*dest_sub = *(char *)src;
		dest_sub++;
		src++;
		i++;
	}
	return (dest);
}
