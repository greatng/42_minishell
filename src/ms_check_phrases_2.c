/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_phrases_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:55:27 by pratanac          #+#    #+#             */
/*   Updated: 2022/06/10 11:25:01 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phrase.h"
#include "../include/minishell.h"

static	int	is_empty(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	print_token_error(char *str, int len)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (str[0] == '\n')
	{
		ft_putstr_fd("newline", STDERR_FILENO);
	}
	else
	{
		write(STDERR_FILENO, str, len);
	}
	ft_putstr_fd("\'\n", STDERR_FILENO);
	return (0);
}

int	print_eof_error(char c)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("unexpected EOF while looking for matching`", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	return (0);
}

int	check_phrase(char *cmd)
{
	char	**lex;

	if (is_empty(cmd))
		return (0);
	if (!is_complete_quote(cmd))
	{
		g_mini.exit_status = 2;
		return (0);
	}
	if (is_pipe_error(cmd))
	{
		g_mini.exit_status = 2;
		return (print_token_error("|", 1));
		return (0);
	}
	lex = lexer(cmd);
	if (!check_lexer(lex))
	{
		g_mini.exit_status = 2;
		free_lexer(lex);
		return (0);
	}
	free_lexer(lex);
	return (1);
}
