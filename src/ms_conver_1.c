/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_conver_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:58:54 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/17 21:22:29 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Duplicate command and translate $VAR
static char	*dup_trans(char *cmd)
{
	char	*tmp;

	tmp = ft_strdup(cmd);
	tmp = translate_cmd(tmp);
	return (tmp);
}

//Count numbers of command for memmory allocation
static size_t	count_cmd(char **cmd_arr)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (cmd_arr[i])
	{
		if (check_redirection(cmd_arr[i]))
		{
			if (cmd_arr[++i])
				i++;
			continue ;
		}
		else
			count++;
		i++;
	}
	return (count + 1);
}

//Duplicate all command, avoid any redirection filename
static void	cmd_to_struct(t_cmd *block_cmd, char ***cmd_arr)
{
	int	i;
	int	j;
	int	idx;

	i = -1;
	while (cmd_arr[++i])
	{
		j = -1;
		idx = 0;
		while (cmd_arr[i][++j])
		{
			if (check_redirection(cmd_arr[i][j]))
			{
				if (cmd_arr[i][++j])
					idx += 2;
				else
					break ;
			}
			else
				block_cmd[i].cmd[j - idx] = dup_trans(cmd_arr[i][j]);
		}
	}
	struct_fd(block_cmd, cmd_arr);
}

//Create struct for command, input, output
t_cmd	*create_struct(char ***cmd_arr)
{
	size_t	i;
	size_t	count;
	size_t	size;
	t_cmd	*block_cmd;

	i = 0;
	while (cmd_arr[i])
		i++;
	block_cmd = ft_calloc(i, sizeof(t_cmd));
	size = i;
	i = 0;
	while (cmd_arr[i])
	{
		count = count_cmd(cmd_arr[i]);
		block_cmd[i].cmd = ft_calloc(count + 1, sizeof(char *));
		block_cmd[i].cmd[count] = NULL;
		block_cmd[i].size = size;
		block_cmd[i].infile = STDIN_FILENO;
		block_cmd[i].outfile = STDOUT_FILENO;
		i++;
	}
	cmd_to_struct(block_cmd, cmd_arr);
	return (block_cmd);
}

//Convert env to g_mini.env
void	convert_arg(int argc, char **argv, char **env)
{
	int	size;
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
	g_mini.env = ft_calloc(size + 1, sizeof(char *));
	g_mini.env[size] = 0;
	while (i < size)
	{
		if (!ft_strncmp("TERM_PROGRAM=", env[i], 13))
			g_mini.env[i] = ft_strdup("TERM_PROGRAM=minihell");
		else
			g_mini.env[i] = ft_strdup(env[i]);
		i++;
	}
}
