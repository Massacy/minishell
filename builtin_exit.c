/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:32:26 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/09 14:49:55 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_out_of_int(const char *str)
{
	long long	num;
	int			sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	num = 0;
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
			num = num * 10 + (*str - '0');
		else
			return (true);
		str++;
	}
	num *= sign;
	if (num > INT_MAX || num < INT_MIN)
		return (true);
	return (false);
}

int	builtin_exit(char **argv, int *last_status)
{
	if (argv[1] == NULL)
		exit(*last_status);
	if (argv[2])
	{
		xperror("exit: too many arguments");
		return (1);
	}
	if (ft_strlen(argv[1]) <= 11 && !is_out_of_int(argv[1]))
	{
		errno = 0;
		exit(ft_atoi(argv[1]));
	}
	xperror("exit: numeric argument required");
	exit(255);
}
