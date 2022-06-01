/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:57:02 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/01 15:24:22 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phrase.h"

static char	*here_doc_join(char *res, char *buf)
{
	char	*tmp;
	char	*return_data;

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

	res = NULL;
	pipe(tmp_pipe);
	while (1)
	{
		buf = readline("> ");
		if (!ft_strncmp(buf, delimit, ft_strlen(delimit) + 1))
			break ;
		res = here_doc_join(res, buf);
	}
	if (buf)
		free(buf);
	write(tmp_pipe[PIPEWR], res, ft_strlen(res));
	close(tmp_pipe[PIPEWR]);
	return (tmp_pipe[PIPERD]);
}
