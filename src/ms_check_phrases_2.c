/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_phrase_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:55:27 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/24 12:02:14 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phrase.h"
#include "../include/minishell.h"

int	check_phrase(char *cmd)
{
	char	**lex;

	if (!is_complete_quote(cmd))
	{
		g_mini.exit_status = 2;
		return (0);
	}
	if (is_pipe_error(cmd))
	{
		g_mini.exit_status = 2;
		printf("bash: syntax error near unexpected token `|\'\n");
		return (0);
	}
	lex = lexer(cmd);
	if (!check_lexer(lex))
	{
		g_mini.exit_status = 2;
		free_lexer(lex);
		return (0);
	}
	g_mini.exit_status = 0;
	free_lexer(lex);
	return (1);
}
