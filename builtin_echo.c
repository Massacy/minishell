/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:55:47 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/23 04:12:56 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_n_option(char *s)
{
	int		i;
	bool	nflg;

	nflg = false;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 'n')
			nflg = true;
		else
			return (false);
		i++;
	}
	return (nflg);
}

int	builtin_echo(char **argv)
{
	int		i;
	bool	nflg;

	nflg = false;
	i = 1;
	while (argv[i] != NULL && argv[i][0] == '-')
	{
		if (is_n_option(argv[i] + 1))
			nflg = true;
		else
			break ;
		i++;
	}
	while (argv[i] != NULL)
	{
		ft_dprintf(1, "%s", argv[i]);
		i++;
		if (argv[i] != NULL)
			ft_dprintf(1, " ");
	}
	if (!nflg)
		ft_dprintf(1, "\n");
	return (0);
}
