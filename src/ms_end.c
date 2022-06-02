/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:39:00 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/02 15:12:00 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	end_of_loop(char *line, t_cmd *tab_cmd)
{
	size_t	i;

	if (line)
	{
		free(line);
		line = NULL;
	}
	i = 0;
	while (i < tab_cmd->size)
	{
		if (tab_cmd[i].cmd)
			free(tab_cmd[i].cmd);
		if (tab_cmd[i].infile != STDIN_FILENO)
			close(tab_cmd[i].infile);
		if (tab_cmd[i].outfile != STDOUT_FILENO)
			close(tab_cmd[i].outfile);
		i++;
	}
	if (tab_cmd)
		free(tab_cmd);
	tab_cmd = NULL;
}
