/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:40:57 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/07 22:05:21 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_builtin(char **cmd)
{
	if (!ft_strncmp("cd", cmd[0], 3))
		change_dir(cmd[1]);
	else if (!ft_strncmp("pwd", cmd[0], 4))
		present_wd();
	else if (!ft_strncmp("echo", cmd[0], 5))
		shell_echo(cmd);
	else if (!ft_strncmp("exit", cmd[0], 5))
		shell_exit();
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
