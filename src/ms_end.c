/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:39:00 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/17 21:23:53 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Clear memory every end-of-loop
void	end_of_loop(t_cmd *block_cmd)
{
	size_t	i;

	i = 0;
	while (i < block_cmd->size)
	{
		if (block_cmd[i].cmd)
			free_lexer(block_cmd[i].cmd);
		if (block_cmd[i].infile != STDIN_FILENO)
			close(block_cmd[i].infile);
		if (block_cmd[i].outfile != STDOUT_FILENO)
			close(block_cmd[i].outfile);
		i++;
	}
	if (block_cmd)
		free(block_cmd);
	block_cmd = NULL;
}
