/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:56:19 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 21:18:50 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//find equal symbol

size_t	strlen_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	check_var_dup(char *cmd)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (g_mini.env[i])
	{
		len = strlen_equal(g_mini.env[i]);
		if (!(ft_strncmp(cmd, g_mini.env[i], len + 1)))
		{
			free(g_mini.env[i]);
			g_mini.env[i] = ft_strdup(cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*add_equal(char *cmd)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (cmd[i] != '=')
	{
		tmp = ft_strjoin(cmd, "=");
		free(cmd);
		return (tmp);
	}
	return (cmd);
}

int	is_var_valid(char *cmd)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (cmd[len] && cmd[len] != '=')
		len++;
	if (!ft_isalpha(cmd[0]))
		return (0);
	while (i < len)
	{
		if (!ft_isalnum(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

void	update_pwd(int mode)
{
	char	buf[1024];
	char	*cwd;
	size_t	i;
	size_t	len;

	i = 0;
	while (g_mini.env[i])
	{
		len = strlen_equal(g_mini.env[i]);
		if (!(ft_strncmp("PWD=", g_mini.env[i], len + 1)))
			break ;
		i++;
	}
	if (mode)
		cwd = ft_strjoin("PWD=", getcwd(buf, 1023));
	else
		cwd = ft_strjoin("OLD", g_mini.env[i]);
	if (!check_var_dup(cwd))
		add_env(cwd);
	free(cwd);
}
