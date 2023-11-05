/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:24:12 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/05 22:43:29 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

void	handler2(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = signum;
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	setup_signals2(void)
{
	setup_signal(SIGQUIT, SIG_IGN);
	setup_signal(SIGINT, handler2);
}

void	reset_signals(void)
{
	setup_signal(SIGQUIT, SIG_DFL);
	setup_signal(SIGINT, SIG_DFL);
}
