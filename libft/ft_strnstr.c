/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:57:50 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/07 16:43:32 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_sub;

	if (*little == '\0')
		return ((char *)big);
	while (len > 0 && *big != '\0')
	{
		i = 0;
		len_sub = len;
		while (big[i] == little[i] && len_sub > 0)
		{
			len_sub--;
			i++;
			if (little[i] == '\0')
				return ((char *)big);
			if (big[i] == '\0')
				return (NULL);
		}
		len--;
		big++;
	}
	return (NULL);
}
