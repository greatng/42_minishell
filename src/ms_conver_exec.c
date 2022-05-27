/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_conver_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:58:54 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/28 02:18:51 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Convert any $VAR to real data
void	convert_var(char ***cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			cmd[i][j] = translate_cmd(cmd[i][j]);
			j++;
		}
		i++;
	}
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

void	shell_execute(char ***cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strncmp("cd", cmd[i][0], 3))
			change_dir(cmd[i][1]);
		else if (!ft_strncmp("pwd", cmd[i][0], 4))
			present_wd();
		else if (!ft_strncmp("echo", cmd[i][0], 5))
			shell_echo(cmd[i]);
		else if (!ft_strncmp("exit", cmd[i][0], 5))
			shell_exit();
		else if (!ft_strncmp("ls", cmd[i][0], 3))
			shell_ls();
		else if (!ft_strncmp("clear", cmd[i][0], 6))
			shell_clear();
		else if (!ft_strncmp("env", cmd[i][0], 4))
			print_env(cmd[i]);
		else if (!ft_strncmp("export", cmd[i][0], 7))
			shell_export(cmd[i]);
		else if (!ft_strncmp("unset", cmd[i][0], 6))
			shell_unset(cmd[i]);
		else if (!ft_strncmp("stty", cmd[i][0], 5))
			enable_echo();
		i++;
	}
}
