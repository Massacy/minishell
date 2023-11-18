/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:30:51 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/05 23:15:09 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

/*   
	入力の偽装
    TIOCSTI   const char *argp
    指定されたバイトを入力キューに挿入する。
*/

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = signum;
	}
}

// rl_replace_line("", 0);がないと現在入力されている内容が実行される
// rl_on_new_line();がないと空白行ができる

void	setup_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

// readline中かつSIGINTの時に、readのバッファを消してread終了にする。
int	rtn_when_sigint(void)
{
	if (g_sig == 0)
		return (0);
	else if (g_sig == SIGINT)
	{
		g_sig = 0;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		return (0);
	}
	return (0);
}

void	setup_signals(void)
{
	if (isatty(STDIN_FILENO))
		rl_event_hook = &rtn_when_sigint;
	setup_signal(SIGQUIT, SIG_IGN);
	setup_signal(SIGINT, handler);
}

// https://tiswww.case.edu/php/chet/readline/readline.html
