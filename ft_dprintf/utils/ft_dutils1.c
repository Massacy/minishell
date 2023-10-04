/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dutils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 04:24:44 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/04 06:30:16 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dutils.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

void	ft_reverse(char *str)
{
	char	tmp;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		tmp = str[len - 1 - i];
		str[len - 1 - i] = str[i];
		str[i] = tmp;
		i++;
	}
}

char	trans_itoh_char(uintptr_t num, bool is_upper)
{
	if (is_upper && num >= 10)
		return (num - 10 + 'A');
	if (num >= 10)
		return (num - 10 + 'a');
	return (num + '0');
}

void	transform_ptr_to_hexadecimal(uintptr_t num, bool is_upper, char *str)
{
	int	i;

	i = -1;
	while (++i < 21)
		str[i] = '\0';
	if (num == 0)
		str[0] = '0';
	i = 0;
	while (num > 0)
	{
		str[i] = trans_itoh_char(num % 16, is_upper);
		num /= 16;
		i++;
	}
	ft_reverse(str);
}

void	transform_uint_to_hexadecimal(unsigned int num, bool is_upper,
		char *str)
{
	int	i;

	i = -1;
	while (++i < 21)
		str[i] = '\0';
	if (num == 0)
		str[0] = '0';
	i = 0;
	while (num > 0)
	{
		str[i] = trans_itoh_char(num % 16, is_upper);
		num /= 16;
		i++;
	}
	ft_reverse(str);
}

size_t	dcheck_x_x(int fd, va_list *arg_ptr, const char *format)
{
	int		d;
	char	str[23];

	d = va_arg(*arg_ptr, unsigned int);
	if (*format == 'x')
		transform_uint_to_hexadecimal(d, false, (char *)str);
	else
		transform_uint_to_hexadecimal(d, true, (char *)str);
	return (write(fd, str, ft_strlen(str)));
}
