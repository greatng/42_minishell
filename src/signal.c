/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:49:20 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/22 17:37:03 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	shell_sighandler(int sig)
{
	if (sig == SIGINT)
		rl_on_new_line();
	if (sig == SIGQUIT)
		return ;
}

void	shell_signal(void)
{
	struct sigaction sa;

	sa.sa_handler = shell_sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// bash Ctrl C -> Sigint -> prompt a new line
// Ctrl D -> exit
// Ctrl \ -> Do nothing