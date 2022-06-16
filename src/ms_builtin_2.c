/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:17:34 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 17:43:19 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i != 1)
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_mini.exit_status = 127;
	}
	else
	{
		while (g_mini.env[i])
		{
			if (g_mini.env[i][0])
				printf("%s\n", g_mini.env[i]);
			i++;
		}
		g_mini.exit_status = 0;
	}
}

void	remove_env(char	*remove_var)
{
	size_t	i;
	size_t	len;
	size_t	size;

	i = 0;
	size = 0;
	while (g_mini.env[size])
		size++;
	while (g_mini.env[i])
	{
		len = strlen_equal(g_mini.env[i]);
		if (!(ft_strncmp(remove_var, g_mini.env[i], len + 1)))
		{
			free(g_mini.env[i]);
			g_mini.env[i] = ft_strdup("");
			return ;
		}
		i++;
	}
}

void	add_env(char *new_var)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while (g_mini.env[i])
		i++;
	tmp = ft_calloc(i + 2, sizeof(char *));
	tmp[i + 1] = NULL;
	tmp[i] = ft_strdup(new_var);
	i = 0;
	while (g_mini.env[i])
	{
		tmp[i] = ft_strdup(g_mini.env[i]);
		free(g_mini.env[i++]);
	}
	free(g_mini.env);
	g_mini.env = tmp;
}

void	shell_export(char **cmd)
{
	size_t	i;

	i = 1;
	while (cmd[i])
	{
		if (!is_var_valid(cmd[i]))
		{
			ft_putstr_fd("export: \'", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
			g_mini.exit_status = 1;
		}
		else
		{
			cmd[i] = add_equal(cmd[i]);
			if (!check_var_dup(cmd[i]))
				add_env(cmd[i]);
			g_mini.exit_status = 0;
		}
		i++;
	}
}

void	shell_unset(char **cmd)
{
	size_t	i;

	i = 1;
	while (cmd[i])
	{
		if (!is_var_valid(cmd[i]))
		{
			ft_putstr_fd("export: \'", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
			g_mini.exit_status = 1;
		}
		else
		{
			cmd[i] = add_equal(cmd[i]);
			remove_env(cmd[i]);
			g_mini.exit_status = 0;
		}
		i++;
	}
}
