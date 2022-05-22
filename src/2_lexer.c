/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:55:17 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/22 12:40:00 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phrase.h"

/*need to handle when pipe on first and last character*/
static int	skip_quote(char *line, int index)
{
	char	quote;
	int		i;

	i = 1;
	quote = line[index];
	while (line[index + i] && line[index + i] != quote)
	{
		i++;
	}
	return (i);
}

/*ugly code TT*/
static int	count_comp(char *line)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 1;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '|')
		{
			flag = 1;
			if (line[i] == '|')
				count++;
		}
		else
		{
			if (flag && ++count)
				flag = 0;
			if (line[i] == '\'' || line[i] == '\"')
				i += skip_quote(line, i);
		}
		i++;
	}
	return (count);
}

static int	count_w(char *line, int index)
{
	int		i;
	int		flag;
	char	quote;

	i = 0;
	flag = 0;
	if (line[index + i] == '|')
		return (1);
	while (line[index + i] && (flag || (line[index + i] != ' ' && line[index + i] != '|')))
	{
		if (!flag && (line[index + i] == '\'' || line[index + i] == '\"'))
		{
			flag = 1;
			quote = line[index + i];
		}
		else if (flag && line[index + i] == quote)
		{
			flag = 0;
		}
		i++;
	}
	return (i);
}

static char	*dup_w(char *line, int index, int word_len)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	while (i < word_len)
	{
		word[i] = line[index + i];
		i++;
	}
	word[i] = '\0';
	return (word);	
}

char	**lexer(char *line)
{
	char	**split;
	int		index;
	int		i;

	split = (char **)malloc(sizeof(char *) * (count_comp(line) + 1));
	if (!split)
		return (NULL);
	i = 0;
	index = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			split[index++] = dup_w(line, i, count_w(line, i));
			i += count_w(line, i);
			continue ;
		}
		i++;
	}
	split[index] = 0;
	return (split);
}
