/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:49:20 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/19 15:26:33 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	shell_sighandler(int sig)
{
	if (sig == SIGINT)
		printf("\nstill can't figure out");
	if (sig == SIGQUIT)
		return ;
}

void	shell_signal(void)
{
	signal(SIGINT, shell_sighandler);
	signal(SIGQUIT, shell_sighandler);
	//signal()
}
