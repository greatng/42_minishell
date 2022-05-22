/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:51:51 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/23 00:26:39 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

extern t_mini	g_mini;

void	change_dir(char *dir)
{
	if (!dir)
		chdir(getenv("HOME"));
	else if (chdir(dir))
		perror("");
}

void	present_wd(void)
{
	char	buf[1024];

	printf("%s\n", getcwd(buf, 1023));
}

static	void	print_echo(char **echo, size_t i, size_t size, int newline)
{
	while (echo[i] && i < size - 1)
	{
		ft_putstr_fd(echo[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		free(echo[i++]);
	}
	if (!newline)
		ft_putendl_fd(echo[i], STDOUT_FILENO);
	else
		ft_putstr_fd(echo[i], STDOUT_FILENO);
	free(echo[i]);
	free(echo);
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
}

void	shell_exit(void)
{
	int	i;

	i = 0;
	while (g_mini.env[i])
		free(g_mini.env[i++]);
	free(g_mini.env);
	printf(RED"\nExiting shell...\n"RES);
	exit(EXIT_SUCCESS);
}
