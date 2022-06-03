/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:50:53 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/03 15:13:39 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_shell_intro(void)
{
	printf(GREEN "Welcome to ...\n");
	printf(NAME1 "\n" NAME2 "\n");
	printf(NAME3 " 's minishell...\n\n" RES);
}

void	enable_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	disable_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	shell_init(int argc, char **argv, char **env)
{
	print_shell_intro();
	convert_arg(argc, argv, env);
	disable_echo();
	shell_signal();
}
