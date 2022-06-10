/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:45:48 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/10 10:37:29 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	free_path(char **path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	if (path)
		free(path);
	return (1);
}

static char	**path_correction(char *env)
{
	char	**path;
	char	*path_var;
	char	*tmp;
	int		i;

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
	int		i;

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

static char	**deep_copy_cmd(char **cmd)
{
	char	**cmd_cpy;
	int		i;

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
	return  (cmd_cpy);
}

char	**check_rightcmd(char **cmd, char **path)
{
	int		i;
	char	*full_path;

	i = -1;
	cmd = deep_copy_cmd(cmd);
	while (path[++i])
	{
		full_path = ft_strjoin(path[i], cmd[0]);
		if (!access(full_path, X_OK))
		{
			free(cmd[0]);
			cmd[0] = full_path;
			break ;
		}
		free(full_path);
	}
	free_path(path);
	return (cmd);
}
