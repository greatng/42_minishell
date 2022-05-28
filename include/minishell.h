/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:16:18 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/28 12:54:11 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "builtin.h"
# include "phrase.h"
# include "quote.h"

# define CLEAR_SCRN "\033[2J \033[H"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define RES "\033[0m"

typedef struct s_mini
{
	char	**env;
	int		exit_status;
}	t_mini;

t_mini	g_mini;

void	shell_init(int argc, char **argv, char **env);
void	enable_echo(void);
//not completed yet
void	shell_signal(void);
//env converter from stack to heap memory, ready to rock
void	convert_arg(int argc, char **argv, char **env);
//translate any $VAR
void	convert_var(char ***cmd);
//execute cmd
void	shell_execute(char ***cmd);

char	*rl_gets(char *line_read);

//free every malloc var at the end of every loop
void	end_of_loop(char *line, char ***cmd);

#endif