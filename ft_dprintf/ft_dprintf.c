/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:13:57 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/04 06:34:03 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/dutils.h"
#include <stdarg.h>
#include <stdbool.h>
// #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	check_format_specifiers(int fd, const char *format, va_list *arg_ptr)
{
	if (*format == 'c')
		return (dcheck_c(fd, arg_ptr));
	else if (*format == 's')
		return (dcheck_s(fd, arg_ptr));
	else if (*format == 'p')
		return (dcheck_p(fd, arg_ptr));
	else if (*format == 'd' || *format == 'i')
		return (dcheck_d_i(fd, arg_ptr));
	else if (*format == 'u')
		return (dcheck_u(fd, arg_ptr));
	else if (*format == 'x' || *format == 'X')
		return (dcheck_x_x(fd, arg_ptr, format));
	else if (*format == '%')
		return (write(fd, "%", 1));
	else
		return (write(fd, format, 1));
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	arg_ptr;
	size_t	cnt;
	size_t	tmp_cnt;
	va_start(arg_ptr, format);
	cnt = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			tmp_cnt = check_format_specifiers(fd,format, &arg_ptr);
		}
		else
			tmp_cnt = write(fd, format, 1);
		format++;
		if (tmp_cnt < 0)
			return (-1);
		cnt += tmp_cnt;
	}
	va_end(arg_ptr);
	return (cnt);
}
