/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_conver_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:24:41 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/01 00:45:39 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_infile(t_cmd *cmd, char **cmd_arg, int j)
{
	if (!ft_strncmp(cmd_arg[j], "<<", 3))
	{
		// if (cmd_arg[j + 1])
		// 	here_doc();
		return ;
	}
	else if (!ft_strncmp(cmd_arg[j], "<", 2))
	{
		if (cmd_arg[j + 1])
		{
			cmd->infile = open(cmd_arg[j + 1], \
				O_RDONLY, 0755);
			if (cmd->infile == -1)
				printf("%s: No such file or directory\n", cmd_arg[j + 1]);
		}
		return ;
	}
	return ;
}

static void	check_outfile(t_cmd *cmd, char **cmd_arg, int j)
{
	if (!ft_strncmp(cmd_arg[j], ">>", 3))
	{
		if (cmd_arg[j + 1])
			cmd->outfile = open(cmd_arg[j + 1], \
				O_RDWR | O_APPEND | O_CREAT, 0755);
		return ;
	}
	else if (!ft_strncmp(cmd_arg[j], ">", 2))
	{
		if (cmd_arg[j + 1])
			cmd->outfile = open(cmd_arg[j + 1], \
				O_WRONLY | O_TRUNC | O_CREAT, 0755);
		return ;
	}
	return ;
}

static void	clean_cmd(char ***cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j]);
			j++;
		}
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	struct_fd(t_cmd *cmd, char ***cmd_arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd_arr[i])
	{
		j = 0;
		while (cmd_arr[i][j])
		{
			check_outfile(&cmd[i], cmd_arr[i], j);
			check_infile(&cmd[i], cmd_arr[i], j);
			j++;
		}
		i++;
	}
	clean_cmd(cmd_arr);
}
