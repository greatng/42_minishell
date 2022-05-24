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

char	*ft_append(char *buffer, char c)
{
	int		i;
	char	*new_buffer;

	i = 0;
	new_buffer = (char *)ft_calloc(sizeof(char), ft_strlen(buffer) + 2);
	if (!new_buffer)
		return (0);
	while (buffer[i])
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	new_buffer[i] = c;
	free(buffer);
	return (new_buffer);
}

char	*ft_join(char *front, char *back)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = (char *) ft_calloc(sizeof(char), \
		ft_strlen(front) + ft_strlen(back) + 1);
	if (!buffer)
		return (0);
	i = 0;
	while (front[i])
	{
		buffer[i] = front[i];
		i++;
	}
	j = 0;
	while (back[j])
	{
		buffer[i + j] = back[j];
		j++;
	}
	free(front);
	free(back);
	return (buffer);
}

char	*ft_append_env(char *buffer, char *command, int *index)
{
	char	*name;
	char	*new_buffer;

	name = get_envname(&command[*index + 1]);
	if (!name[0])
	{
		if (command[*index + 1] != '?')
			return (ft_append(buffer, '$'));
		new_buffer = ft_join(buffer, ft_itoa(g_mini.exit_status));
		*index += 1;
	}
	else
	{
		new_buffer = ft_join(buffer, ft_getenv(name, g_mini.env));
		*index += ft_strlen(name);
	}
	free(name);
	return (new_buffer);
}

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
		else if (command[i] == '$' && quote != '\'') // input is position ['$']
			buffer = ft_append_env(buffer, command, &i);
		else
			buffer = ft_append(buffer, command[i]);
		i++;
	}
	if (command)
		free(command);
	return (buffer);
}
