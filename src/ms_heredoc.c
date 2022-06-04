/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:57:02 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/04 11:51:32 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phrase.h"

static char	*need_translate(char *delimit, int *mode)
{
	int	c;
	int	len;

	delimit = ft_strdup(delimit);
	c = delimit[0];
	if (c == '\'' || c == '\"')
	{
		len = ft_strlen(delimit);
		if (len > 1 && delimit[len - 1] == c)
		{
			delimit = translate_cmd(delimit);
			*mode = 0;
			return (delimit);
		}
	}
	*mode = 1;
	return (delimit);
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

int	here_doc(char *delimit)
{
	char	*buf;
	char	*res;
	int		tmp_pipe[2];
	int		mode;

	res = NULL;
	delimit = need_translate(delimit, &mode);
	pipe(tmp_pipe);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		if (!ft_strncmp(buf, delimit, ft_strlen(delimit) + 1))
			break ;
		res = here_doc_join(res, buf, mode);
	}
	if (buf)
		free(buf);
	free(delimit);
	write(tmp_pipe[PIPEWR], res, ft_strlen(res));
	close(tmp_pipe[PIPEWR]);
	free(res);
	return (tmp_pipe[PIPERD]);
}
