/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:45:48 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/17 21:14:01 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**path_correction(char *env)
{
	char	**path;
	char	*path_value;
	char	*tmp;
	size_t	i;

	path_value = ft_strchr(env, '/');
	if (!path_value)
		return (NULL);
	path = ft_split(path_value, ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
		i++;
	}
	return (path);
}

char	**get_path(void)
{
	size_t	i;

	i = 0;
	while (g_mini.env[i])
	{
		if (!ft_strncmp(g_mini.env[i], "PATH=", 5))
			return (path_correction(g_mini.env[i]));
		i++;
	}
	return (NULL);
}

static char	**deep_copy(char **cmd)
{
	char		**cmd_cpy;
	size_t		i;

	i = 0;
	while (cmd[i])
		i++;
	cmd_cpy = ft_calloc(i + 1, sizeof(char *));
	cmd_cpy[i] = NULL;
	i = 0;
	while (cmd[i])
	{
		cmd_cpy[i] = ft_strdup(cmd[i]);
		i++;
	}
	return (cmd_cpy);
}

char	**check_rightcmd(char **cmd, char **path)
{
	size_t		i;
	char		*full_path;

	i = 0;
	cmd = deep_copy(cmd);
	while (path && path[i])
	{
		full_path = ft_strjoin(path[i], cmd[0]);
		if (!access(full_path, X_OK))
		{
			free(cmd[0]);
			cmd[0] = full_path;
			break ;
		}
		free(full_path);
		i++;
	}
	if (path)
		free_lexer(path);
	return (cmd);
}
