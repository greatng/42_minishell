/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:39:00 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/16 20:13:01 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Clear memory every end-of-loop
void	end_of_loop(t_cmd *tab_cmd)
{
	size_t	i;

	i = 0;
	if (!tab_cmd)
		return ;
	while (i < tab_cmd->size)
	{
		if (tab_cmd[i].cmd)
			free_lexer(tab_cmd[i].cmd);
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
