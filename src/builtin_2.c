/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:17:34 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/23 13:16:18 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_mini	g_mini;

void	print_env(char **cmd)
{
	int	i;
	
	i = 0;
	while (cmd[i])
		i++;
	if (i != 1)
	{
		printf("%s: %s: No such file or directory\n", cmd[0], cmd[1]);
		g_mini.exit_status = 127;
		return ;
	}
	else
		i = 1;
	while (g_mini.env[i])
		printf("%s\n", g_mini.env[i++]);
}