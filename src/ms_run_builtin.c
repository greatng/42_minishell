/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:40:57 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/09 01:14:27 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_numeric(char	*input)
{
	int	i;

	i = 0;
	if (input && (input[i] == '+' || input[i] == '-'))
		i++;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static void	set_exit(char **cmd)
{
	unsigned int	i;

	i = 0;
	if (!is_numeric(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_mini.exit_status = 255;
		return ;
	}
	i = ft_atoi(cmd[1]);
	g_mini.exit_status = i % 256;
	return ;
}

static int	check_arg_exit(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	if (i <= 2)
	{
		if (i > 1)
			set_exit(cmd);
		return (1);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	g_mini.exit_status = 1;
	return (0);
}

int	run_builtin(char **cmd, t_cmd *tab_cmd)
{
	if (!ft_strncmp("cd", cmd[0], 3))
		change_dir(cmd[1]);
	else if (!ft_strncmp("pwd", cmd[0], 4))
		present_wd();
	else if (!ft_strncmp("echo", cmd[0], 5))
		shell_echo(cmd);
	else if (!ft_strncmp("exit", cmd[0], 5))
	{
		if (!check_arg_exit(cmd))
			return (1);
		end_of_loop(tab_cmd);
		shell_exit();
	}
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
