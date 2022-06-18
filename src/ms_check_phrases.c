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

/* return 0 if pharase is in complete */
/* return 1 when phrase is complete */
int	is_complete_quote(char *str)
{
	int		i;
	int		flag;
	char	quote;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (!flag && (str[i] == '\'' || str[i] == '\"'))
		{
			flag = 1;
			quote = str[i];
		}
		else if (flag && str[i] == quote)
		{
			flag = 0;
		}
		i++;
	}
	if (flag)
	{
		print_eof_error(quote);
		return (0);
	}
	return (1);
}

int	is_pipe_error(char *line)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (last)
				return (1);
			last = 1;
		}
		else
			last = 0;
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_quote(line, i);
		if (line[i])
			i++;
	}
	if (i > 0 && line[i - 1] == '|')
		return (2);
	return (0);
}

int	is_syntax(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '<' || c == '>')
		return (2);
	else if (c == '|')
		return (3);
	return (0);
}

static int	check_syntax(char *cmd)
{
	if (!ft_strncmp(cmd, "<<", ft_strlen(cmd)))
	{
		return (1);
	}
	else if (!ft_strncmp(cmd, ">>", ft_strlen(cmd)))
	{
		return (1);
	}
	if (cmd[0] != cmd[1])
	{
		print_token_error(&cmd[1], ft_strlen(&cmd[1]));
	}
	else
	{
		print_token_error(&cmd[1], ft_strlen(&cmd[2]));
	}
	return (0);
}

/*1 = pass 0 = fail*/
int	check_lexer(char **lexer)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (lexer[i])
	{
		if (is_syntax(lexer[i][0]) == 2 && !check_syntax(lexer[i]))
			return (0);
		if (flag > 0 && (is_syntax(lexer[i][0]) >= flag))
			return (print_token_error(lexer[i], ft_strlen(lexer[i])));
		flag = is_syntax(lexer[i][0]);
		i++;
	}
	if (flag > 0)
		return (print_token_error("\n", 1));
	return (1);
}
