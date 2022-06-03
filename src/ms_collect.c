/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:58:15 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/03 18:17:31 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	collect_status(int size)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	g_mini.exit_status = 0;
	while (i < size)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) > g_mini.exit_status)
				g_mini.exit_status = WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status))
			g_mini.exit_status = status + (1 << 7);
		i++;
	}
}