/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_conver_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:58:54 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/28 12:53:26 by pngamcha         ###   ########.fr       */
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

static int	run_builtin(char **cmd)
{
	if (!ft_strncmp("cd", cmd[0], 3))
		change_dir(cmd[1]);
	else if (!ft_strncmp("pwd", cmd[0], 4))
		present_wd();
	else if (!ft_strncmp("echo", cmd[0], 5))
		shell_echo(cmd);
	else if (!ft_strncmp("exit", cmd[0], 5))
		shell_exit();
	else if (!ft_strncmp("ls", cmd[0], 3))
		shell_ls();
	else if (!ft_strncmp("clear", cmd[0], 6))
		shell_clear();
	else if (!ft_strncmp("env", cmd[0], 4))
		print_env(cmd);
	else if (!ft_strncmp("export", cmd[0], 7))
		shell_export(cmd);
	else if (!ft_strncmp("unset", cmd[0], 6))
		shell_unset(cmd);
	else
		return (0);
	return (1);
}	

void	shell_execute(char ***cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		run_builtin(cmd[i]);
		i++;
	}
}
