/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:41:18 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/21 22:12:26 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "\x1b[31mFatal Error: %s\n\x1b[39m", msg);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "assert Error: %s\n", msg);
	exit(255);
}

void	builtin_error(const char *func, const char *str, const char *err)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", func);
	if (str)
		ft_dprintf(STDERR_FILENO, "`%s': ", str);
	ft_dprintf(STDERR_FILENO, "%s\n", err);
}

void	todo(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

// void command_not_found_error(const char *msg) __attribute__((noreturn));

// void command_not_found_error(const char *cmd)
// {
// 	ft_dprintf(STDERR_FILENO,
//			"\x1b[31mCommand not found: \"%s\" does not found\n\x1b[39m", cmd);
// 	exit(127);
// }
