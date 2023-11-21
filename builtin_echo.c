/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:55:47 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/22 04:32:27 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_n_option(char *s)
{
	int		i;
	bool 	nflg;

	printf("s = %s\n", s);
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
	// if (ft_strlen(argv[1]) == 2 && ft_strncmp(argv[1], "-n", 2) == 0)
	// {
	// 	nflg = true;
	// 	i++;
	// }

	while (argv[i] != NULL && argv[i][0] == '-')
	{
		if(is_n_option(argv[i]+1))
			nflg = true;
		else
			break;
		i++;
	}
	printf("????\n");
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
