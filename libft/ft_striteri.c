/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:40:53 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 21:24:17 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	len;
	int		i;

	if (s == NULL || f == NULL)
		return ;
	len = ft_strlen(s);
	i = -1;
	while (++i < (int)len)
		f(i, &s[i]);
}
