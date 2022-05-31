/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_conver_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:58:54 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/01 00:37:44 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	count_cmd(char **cmd_arr)
{
	size_t	i;

	i = 0;
	while (cmd_arr[i])
	{
		if (!ft_strncmp(cmd_arr[i], ">>", 3) || \
			!ft_strncmp(cmd_arr[i], "<<", 3) || \
			!ft_strncmp(cmd_arr[i], ">", 2) || \
			!ft_strncmp(cmd_arr[i], "<", 2))
			break ;
		i++;
	}
	return (i);
}

static void	cmd_to_struct(t_cmd *cmd, char ***cmd_arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd_arr[i])
	{
		j = 0;
		while (cmd_arr[i][j])
		{
			if (!ft_strncmp(cmd_arr[i][j], ">>", 3) || \
				!ft_strncmp(cmd_arr[i][j], "<<", 3) || \
				!ft_strncmp(cmd_arr[i][j], ">", 2) || \
				!ft_strncmp(cmd_arr[i][j], "<", 2))
				break ;
			else
			{
				cmd[i].cmd[j] = ft_strdup(cmd_arr[i][j]);
				cmd[i].cmd[j] = translate_cmd(cmd[i].cmd[j]);
			}
			j++;
		}
		i++;
	}
	struct_fd(cmd, cmd_arr);
}

t_cmd	*create_struct(char ***cmd_arr)
{
	size_t	i;
	size_t	count;
	size_t	size;
	t_cmd	*tab_cmd;

	i = 0;
	while (cmd_arr[i])
		i++;
	tab_cmd = ft_calloc(i, sizeof(t_cmd));
	size = i;
	i = 0;
	while (cmd_arr[i])
	{
		count = count_cmd(cmd_arr[i]);
		tab_cmd[i].cmd = ft_calloc(count + 1, sizeof(char *));
		tab_cmd[i].cmd[count] = NULL;
		tab_cmd[i].size = size;
		tab_cmd[i].infile = STDIN_FILENO;
		tab_cmd[i].outfile = STDOUT_FILENO;
		i++;
	}
	cmd_to_struct(tab_cmd, cmd_arr);
	return (tab_cmd);
}
//Convert env to g_mini.env

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
	g_mini.env = ft_calloc(size + 1, sizeof(char *));
	g_mini.env[size] = 0;
	while (i < size)
	{
		len = ft_strlen(env[i]) + 1;
		g_mini.env[i] = ft_calloc(len, sizeof(char));
		ft_strlcpy(g_mini.env[i], env[i], len);
		i++;
	}
}
