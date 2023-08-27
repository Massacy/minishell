/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:23:34 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 22:27:06 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t number, size_t size)
{
	void	*ptr;

	if (number && (size > SIZE_MAX / number))
	{
		errno = ENOMEM;
		return (NULL);
	}
	ptr = malloc(number * size);
	if (ptr != NULL)
		ft_bzero(ptr, number * size);
	return (ptr);
}
