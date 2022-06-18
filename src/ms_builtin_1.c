/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:51:51 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/17 23:45:29 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

void	change_dir(char *dir_path)
{
	size_t	i;
	char	*dir;

	i = -1;
	dir = dir_path;
	update_pwd(1);
	if (!dir)
	{
		while (g_mini.env[++i])
		{
			if (!ft_strncmp("HOME=", g_mini.env[i], 5))
			{
				dir = ft_strchr(g_mini.env[i], '/');
				break ;
			}
		}
	}
	if (dir && chdir(dir))
		perror(dir_path);
	else
	{
		update_pwd(0);
		update_pwd(1);
	}
	g_mini.exit_status = errno;
}

void	present_wd(void)
{
	char	buf[1024];

	printf("%s\n", getcwd(buf, 1023));
	g_mini.exit_status = 0;
}

static	void	print_echo(char **echo, size_t i, size_t size, int newline)
{
	while (echo[i] && i < size - 1)
	{
		ft_putstr_fd(echo[i++], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!newline)
		ft_putendl_fd(echo[i], STDOUT_FILENO);
	else
		ft_putstr_fd(echo[i], STDOUT_FILENO);
}

void	shell_echo(char **echo)
{
	size_t	size;
	size_t	i;
	int		newline;

	size = 0;
	i = 1;
	newline = 0;
	while (echo[size])
		size++;
	if (size > 1)
	{
		if (!ft_strncmp("-n", echo[1], 3))
		{
			i++;
			newline++;
		}
		print_echo(echo, i, size, newline);
	}
	g_mini.exit_status = 0;
}

void	shell_exit(void)
{
	enable_echo();
	clean_env();
	rl_clear_history();
	ft_putendl_fd(RED"Exiting shell..."RES, STDERR_FILENO);
	exit(g_mini.exit_status);
}
