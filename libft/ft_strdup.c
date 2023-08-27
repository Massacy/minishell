/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:59:07 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/13 19:15:08 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr;
	int		i;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (*s != '\0')
	{
		ptr[i] = *s;
		s++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
