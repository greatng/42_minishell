/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:39:00 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/26 17:24:33 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	end_of_loop(char *line, char ***cmd)
{
	size_t	i;
	size_t	j;

	free(line);
	line = NULL;
	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j]);
			cmd[i][j] = NULL;
			j++;
		}
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free (cmd);
	cmd = NULL;
}
