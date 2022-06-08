/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:39:35 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/09 01:52:03 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_heredoc(char *delimit, char *res, char *buf)
{
	free(delimit);
	free(res);
	if (buf)
		free(buf);
	clean_env();
}