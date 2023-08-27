/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 03:43:20 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/19 21:05:40 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_cal_digit_max(int n)
{
	int	d;
	int	tmp;

	d = 1000000000;
	while (d)
	{
		tmp = n / d;
		if (tmp != 0)
			break ;
		d /= 10;
	}
	return (d);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		d_max;
	char	tmp;

	if (n == 0)
		write(fd, "0", 1);
	d_max = ft_cal_digit_max(n);
	if (n < 0)
		write(fd, "-", 1);
	while (d_max)
	{
		if (n < 0)
			tmp = -(n / d_max) + '0';
		else
			tmp = n / d_max + '0';
		write(fd, &tmp, 1);
		n %= d_max;
		d_max /= 10;
	}
}
