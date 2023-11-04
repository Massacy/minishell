/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:55:47 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/04 19:05:53 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	int		i;
	bool	nflg;

	nflg = false;
	i = 0;
	if (ft_strlen(argv[1]) == 2 && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		nflg = true;
		i++;
	}
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i] != NULL)
			printf(" ");
	}
	if (!nflg)
		printf("\n");
	return (0);
}
