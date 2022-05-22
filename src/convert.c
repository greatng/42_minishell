/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:58:54 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/23 00:22:14 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_mini	g_mini;

void	print_env(void)
{
	for (int i = 0; g_mini.env[i]; i++)
		printf("%s\n", g_mini.env[i]);
}

void	convert_arg(int argc, char **argv, char **env)
{
	int	size;
	int	len;
	int	i;

	if (argc != 1 || !argv[0])
	{
		printf("Please run by using ./minishell\n");
		exit(0);
	}
	size = 0;
	i = 0;
	while (env[size])
		size++;
	g_mini.env = ft_calloc(sizeof(char *), size + 1);
	g_mini.env[size] = 0;
	while (i < size)
	{
		len = ft_strlen(env[i]) + 1;
		g_mini.env[i] = ft_calloc(sizeof(char), len);
		ft_strlcpy(g_mini.env[i], env[i], len);
		//printf("%d %s\n", i, g_mini.env[i]);
		i++;
	}
}