/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dutils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 04:19:08 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/04 06:27:23 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dutils.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

size_t	dcheck_u(int fd, va_list *arg_ptr)
{
	unsigned int	u;
	char			*s;
	size_t			len;

	u = va_arg(*arg_ptr, unsigned int);
	s = ft_uitoa(u);
	len = write(fd, s, ft_strlen(s));
	free(s);
	return (len);
}

size_t	dcheck_d_i(int fd, va_list *arg_ptr)
{
	int		d;
	char	*s;
	size_t	len;

	d = va_arg(*arg_ptr, int);
	s = ft_itoa(d);
	len = write(fd, s, ft_strlen(s));
	free(s);
	return (len);
}

size_t	dcheck_p(int fd, va_list *arg_ptr)
{
	void	*p;
	char	str[23];

	p = va_arg(*arg_ptr, void *);
	str[0] = '0';
	str[1] = 'x';
	transform_ptr_to_hexadecimal((uintptr_t)p, false, (char *)&str[2]);
	return (write(fd, str, ft_strlen((char *)str)));
}

size_t	dcheck_s(int fd, va_list *arg_ptr)
{
	char	*s;

	s = va_arg(*arg_ptr, char *);
	if (s == NULL)
		s = "(null)";
	return (write(fd, s, ft_strlen(s)));
}

size_t	dcheck_c(int fd, va_list *arg_ptr)
{
	char	c;

	c = (char)va_arg(*arg_ptr, int);
	return (write(fd, &c, 1));
}
