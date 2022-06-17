/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_conver_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:24:41 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/17 21:20:01 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Check how to read infile
static void	check_infile(t_cmd *cmd, char **cmd_arg, int j)
{
	if (!ft_strncmp(cmd_arg[j], "<<", 3))
	{
		if (cmd_arg[j + 1])
		{
			if (cmd->infile != STDIN_FILENO)
				close(cmd->infile);
			cmd->infile = here_doc(cmd_arg[j + 1]);
		}
	}
	else if (!ft_strncmp(cmd_arg[j], "<", 2))
	{
		if (cmd_arg[j + 1])
		{
			cmd_arg[j + 1] = translate_cmd(cmd_arg[j + 1]);
			if (cmd->infile != STDIN_FILENO)
				close(cmd->infile);
			cmd->infile = open(cmd_arg[j + 1], \
				O_RDONLY, 0755);
			if (cmd->infile == -1)
				perror(cmd_arg[j + 1]);
		}
	}
}

//Check how to write outfile
static void	check_outfile(t_cmd *cmd, char **cmd_arg, int j)
{
	if (!ft_strncmp(cmd_arg[j], ">>", 3))
	{
		if (cmd_arg[j + 1])
		{
			cmd_arg[j + 1] = translate_cmd(cmd_arg[j + 1]);
			if (cmd->outfile != STDOUT_FILENO)
				close(cmd->outfile);
			cmd->outfile = open(cmd_arg[j + 1], \
				O_RDWR | O_APPEND | O_CREAT, 0755);
		}
	}
	else if (!ft_strncmp(cmd_arg[j], ">", 2))
	{
		if (cmd_arg[j + 1])
		{
			cmd_arg[j + 1] = translate_cmd(cmd_arg[j + 1]);
			if (cmd->outfile != STDOUT_FILENO)
				close(cmd->outfile);
			cmd->outfile = open(cmd_arg[j + 1], \
				O_WRONLY | O_TRUNC | O_CREAT, 0755);
		}
	}
}

//Open file for input, output and assign in Struct fd
void	struct_fd(t_cmd *block_cmd, char ***cmd_arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd_arr[i])
	{
		j = 0;
		while (cmd_arr[i][j])
		{
			if (check_redirection(cmd_arr[i][j]))
			{
				check_outfile(&block_cmd[i], cmd_arr[i], j);
				check_infile(&block_cmd[i], cmd_arr[i], j);
			}
			j++;
		}
		i++;
	}
	free_parser(cmd_arr);
}

//Check if it redirection
int	check_redirection(char *redirect)
{
	if (!ft_strncmp(redirect, ">>", 3) || \
			!ft_strncmp(redirect, "<<", 3) || \
			!ft_strncmp(redirect, ">", 2) || \
			!ft_strncmp(redirect, "<", 2))
		return (1);
	return (0);
}
