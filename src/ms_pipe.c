/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:32:56 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/17 09:47:05 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_env(void)
{
	int	i;

	i = 0;
	while (g_mini.env[i])
		free(g_mini.env[i++]);
	free(g_mini.env);
}

static void	reset_fd(int *pipefd, int *savefd)
{
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

static void	execute_cmd(char **cmd, t_cmd *tab_cmd)
{
	pid_t	pid;
	char	**path;

	pid = fork();
	if (!pid)
	{
		path = get_path();
		cmd = check_rightcmd(cmd, path);
		end_of_loop(tab_cmd);
		if (execve(cmd[0], cmd, g_mini.env) == -1)
		{
			clean_env();
			ft_putstr_fd(cmd[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			exit(127);
		}
	}
}

void	shell_execute(t_cmd *tab_cmd)
{
	int	i;
	int	savefd[2];
	int	pipefd[2];
	int	count;

	i = -1;
	count = 0;
	savefd[1] = dup(STDOUT_FILENO);
	savefd[0] = dup(STDIN_FILENO);
	shell_child_signal();
	while (++i < (int)tab_cmd->size)
	{
		if (!tab_cmd[i].cmd[0])
			break ;
		redirect_fd(tab_cmd, i, pipefd);
		if (!run_builtin(tab_cmd[i].cmd, tab_cmd))
		{
			count++;
			execute_cmd(tab_cmd[i].cmd, tab_cmd);
		}
		reset_fd(pipefd, savefd);
	}
	collect_status(count);
	shell_signal();
}
