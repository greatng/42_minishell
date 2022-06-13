/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_translate_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:02:27 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 12:03:03 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/quote.h"

char	*translate_cmd(char *command)
{
	char	*buffer;
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (0);
	while (command && command[i])
	{
		if (!quote && (command[i] == '\'' || command[i] == '\"'))
			quote = command[i];
		else if (command[i] == quote)
			quote = 0;
		else if (command[i] == '$' && quote != '\'')
			buffer = ft_append_env(buffer, command, &i);
		else
			buffer = ft_append(buffer, command[i]);
		i++;
	}
	if (command)
		free(command);
	return (buffer);
}

char	*translate_cmd_hd(char *command)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (0);
	while (command && command[i])
	{
		if (command[i] == '$')
			buffer = ft_append_env(buffer, command, &i);
		else
			buffer = ft_append(buffer, command[i]);
		i++;
	}
	if (command)
		free(command);
	return (buffer);
}
