/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_rl_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:18:26 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/10 11:23:38 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*rl_gets(char *line_read)
{
	char	buf[100];
	char	*wd;
	char	*shell;

	getcwd(buf, 99);
	wd = ft_strrchr(buf, '/');
	ft_strlcat(wd, RED" § "RES, ft_strlen(wd) + 20);
	shell = ft_strjoin(GREEN "minihell "RES, wd);
	line_read = readline(shell);
	free(shell);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}
