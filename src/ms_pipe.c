/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:32:56 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/02 22:25:21 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	reset_fd(t_cmd *tab_cmd, size_t i, int *pipefd, int *savefd)
{
	if (tab_cmd[i].outfile != STDOUT_FILENO)
		close(tab_cmd[i].outfile);
	if (tab_cmd[i].infile != STDIN_FILENO)
		close(tab_cmd[i].infile);
	dup2(savefd[1], STDOUT_FILENO);
	dup2(savefd[0], STDIN_FILENO);
	close(pipefd[PIPEWR]);
}

static void	redirect_fd(t_cmd *tab_cmd, size_t i, int *pipefd)
{
	if (i > 0 && tab_cmd[i].infile == STDIN_FILENO)
	{
		dup2(pipefd[PIPERD], STDIN_FILENO);
		close(pipefd[PIPERD]);
	}
	else
		dup2(tab_cmd[i].infile, STDIN_FILENO);
	pipe(pipefd);
	if (tab_cmd[i].outfile == STDOUT_FILENO && i < tab_cmd->size - 1)
		dup2(pipefd[PIPEWR], STDOUT_FILENO);
	else
		dup2(tab_cmd[i].outfile, STDOUT_FILENO);
}

static void	execute_cmd(char **cmd)
{
	pid_t	pid;
	char	**path;

	pid = fork();
	if (!pid)
	{
		path = get_path();
		if (check_rightcmd(cmd, path))
			execve(cmd[0], cmd, g_mini.env);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		g_mini.exit_status = 127;
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}

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

void	shell_execute(t_cmd *tab_cmd)
{
	size_t	i;
	int		savefd[2];
	int		pipefd[2];

	i = 0;
	savefd[1] = dup(STDOUT_FILENO);
	savefd[0] = dup(STDIN_FILENO);
	while (i < tab_cmd->size)
	{
		if (!tab_cmd[i].cmd[0])
			break ;
		redirect_fd(tab_cmd, i, pipefd);
		if (!run_builtin(tab_cmd[i].cmd))
			execute_cmd(tab_cmd[i].cmd);
		reset_fd(tab_cmd, i, pipefd, savefd);
		i++;
	}
}
