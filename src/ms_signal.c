/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:49:20 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/03 17:45:21 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	kill_child(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		kill(0, SIGINT);
		signal(SIGINT, SIG_DFL);
	}
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		kill(0, SIGQUIT);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	shell_child_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = kill_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	shell_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_mini.exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	shell_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = shell_sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// bash Ctrl C -> Sigint -> prompt a new line
// Ctrl D -> exit
// Ctrl \ -> Do nothing