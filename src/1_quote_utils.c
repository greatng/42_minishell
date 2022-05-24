/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_quote_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:03:53 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 12:03:54 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/quote.h"

static int	is_envname(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*get_envname(char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (str[i] && is_envname(str[i]))
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	if (!name)
		return (0);
	j = 0;
	while (j < i)
	{
		name[j] = str[j];
		j++;
	}
	name[j] = 0;
	return (name);
}

static int	match_env(char *name, char *path)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (name[i] != path[i])
			return (0);
		i++;
	}
	if (path[i] == '=')
		return (1);
	return (0);
}

static char	*get_var(char *env)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
		i++;
	buffer = (char *)ft_calloc(sizeof(char), ft_strlen(env) - i);
	if (!buffer)
		return (0);
	i++;
	while (env[i])
	{
		buffer[j] = env[i];
		i++;
		j++;
	}
	return (buffer);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	char	*buffer;

	i = 0;
	while (env && env[i] && !match_env(name, env[i]))
		i++;
	if (!env || !env[i])
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (0);
	}
	else
		buffer = get_var(env[i]);
	return (buffer);
}

/*
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
	if (command)
		free(command);
	return (buffer);
}
*/
