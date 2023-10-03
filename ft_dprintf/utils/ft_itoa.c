/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:17:30 by imasayos          #+#    #+#             */
/*   Updated: 2023/04/07 04:31:10 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	count_digit(int n)
{
	int	tmp;
	int	cnt;

	tmp = n;
	cnt = 0;
	while (tmp != 0)
	{
		tmp /= 10;
		cnt++;
	}
	return (cnt);
}

int	ft_power(int n)
{
	int	i;
	int	tmp;

	tmp = 1;
	i = -1;
	while (++i < n)
		tmp *= 10;
	return (tmp);
}

char	*ft_itoa(int n)
{
	int		cnt;
	char	*ptr;
	int		i;
	int		d;

	cnt = count_digit(n);
	i = 0;
	ptr = malloc(cnt + 2);
	if (ptr == NULL)
		return (NULL);
	if (n < 0)
		ptr[i++] = '-';
	d = ft_power(cnt - 1);
	while (d > 0)
	{
		ptr[i] = (n / d) + '0';
		if (n / d < 0)
			ptr[i] = -(n / d) + '0';
		n %= d;
		d /= 10;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	count_digit_u(unsigned int n)
{
	unsigned int	tmp;
	int				cnt;

	tmp = n;
	cnt = 0;
	while (tmp != 0)
	{
		tmp /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_uitoa(unsigned int n)
{
	int		cnt;
	char	*ptr;
	int		i;
	int		d;

	cnt = count_digit_u(n);
	i = 0;
	ptr = malloc(cnt + 2);
	if (ptr == NULL)
		return (NULL);
	d = ft_power(cnt - 1);
	while (d > 0)
	{
		ptr[i] = (n / d) + '0';
		n %= d;
		d /= 10;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
