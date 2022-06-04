/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_quote_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:03:53 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 12:03:54 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/quote.h"

char	*unquote(char *command)
{
	char	*buffer;
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	buffer = ft_calloc(1, 1);
	while (command && command[i])
	{
		if (!quote && (command[i] == '\'' || command[i] == '\"'))
			quote = command[i];
		else if (command[i] == quote)
			quote = 0;
		else
			buffer = ft_append(buffer, command[i]);
		i++;
	}
	// if (command)
	// 	free(command);
	return (buffer);
}

int		find_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}