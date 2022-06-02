/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:45:48 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/02 15:01:53 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_rightcmd(char **cmd, char **path)
{
	int	i;
	char	*full_path;

	i = -1;
	if (!path)
		return (1);
	while (path[++i])
	{
		full_path = ft_strjoin(path[i], cmd[0]);
		if (!access(full_path, X_OK))
		{
			free(cmd[0]);
			cmd[0] = full_path;
			return (1);
		}
		free (full_path);
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (0);
}

static char	**path_correction(char *env)
{
	char	**path;
	char	*path_var;
	char	*tmp;
	int	i;

	path_var = ft_strchr(env, '/');
	path = ft_split(path_var, ':');
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
	}
	return (path);
}

char	**get_path(void)
{
	char	**path;
	int	i;

	i = -1;
	path = NULL;
	while (g_mini.env[++i])
	{
		if (!ft_strncmp(g_mini.env[i], "PATH=", 5))
			break ;
	}
	if (!ft_strncmp(g_mini.env[i], "PATH=", 5))
		path = path_correction(g_mini.env[i]);
	return (path);
}