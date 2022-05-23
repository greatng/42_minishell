/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:17:34 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/23 10:28:15 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_mini	g_mini;

void	print_env(void)
{
	int	i;
	
	i = 0;
	while (g_mini.env[i])
		printf("%s\n", g_mini.env[i++]);
}