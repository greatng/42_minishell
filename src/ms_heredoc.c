/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:57:02 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/05 21:55:47 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phrase.h"

static void	heredoc_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		kill(0, SIGINT);
		signal(SIGINT, SIG_DFL);
		write(1, "\n", 1);
	}
}

void	shell_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static char	*here_doc_join(char *res, char *buf, int mode)
{
	char	*tmp;
	char	*return_data;

	if (mode)
		buf = translate_cmd(buf);
	tmp = ft_strjoin(buf, "\n");
	free(buf);
	buf = tmp;
	return_data = ft_strjoin(res, buf);
	free(buf);
	free(res);
	return (return_data);
}

static void	child_here_doc(int *tmp_pipe, char *delimit)
{
	char	*buf;
	char	*res;
	int		mode;

	res = NULL;
	close(tmp_pipe[PIPERD]);
	mode = !find_quote(delimit);
	delimit = unquote(delimit);
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strncmp(buf, delimit, ft_strlen(delimit) + 1))
		{
			if (buf)
				free(buf);
			write(tmp_pipe[PIPEWR], res, ft_strlen(res));
			close(tmp_pipe[PIPEWR]);
			free(res);
			free(delimit);
			break ;
		}
		res = here_doc_join(res, buf, mode);
	}
	exit (0);
}

int	here_doc(char *delimit)
{
	int		tmp_pipe[2];
	int		pid;
	int		status;

	pipe(tmp_pipe);
	shell_heredoc_signal();
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		child_here_doc(tmp_pipe, delimit);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(tmp_pipe[PIPEWR]);
	}
	shell_signal();
	return (tmp_pipe[PIPERD]);
}

// int	here_doc(char *delimit)
// {
// 	char	*buf;
// 	char	*res;
// 	int		tmp_pipe[2];
// 	int		mode;

// 	res = NULL;
// 	mode = !find_quote(delimit);
// 	delimit = unquote(delimit);
// 	pipe(tmp_pipe);
// 	while (1)
// 	{
// 		buf = readline("> ");
// 		if (!buf)
// 		{
// 			printf("\n");
// 			break;
// 		}
// 		if (!ft_strncmp(buf, delimit, ft_strlen(delimit) + 1))
// 			break ;
// 		res = here_doc_join(res, buf, mode);
// 	}
// 	if (buf)
// 		free(buf);
// 	free(delimit);
// 	write(tmp_pipe[PIPEWR], res, ft_strlen(res));
// 	close(tmp_pipe[PIPEWR]);
// 	free(res);
// 	return (tmp_pipe[PIPERD]);
// }