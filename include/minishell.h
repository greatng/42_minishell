/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:16:18 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/01 10:11:10 by pngamcha         ###   ########.fr       */
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
# include <fcntl.h>

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

# define PIPERD 0
# define PIPEWR 1

typedef struct s_mini
{
	char	**env;
	int		exit_status;
}	t_mini;

t_mini	g_mini;

typedef struct s_cmd
{
	char	**cmd;
	int	infile;
	int	outfile;
	size_t	size;
}	t_cmd;

//Init part
void	shell_init(int argc, char **argv, char **env);
void	enable_echo(void);
void	shell_signal(void);
void	convert_arg(int argc, char **argv, char **env);

//translate any $VAR, Convert char *** to struct
int	here_doc(char *delimit);
void	struct_fd(t_cmd *cmd, char ***cmd_arr);
t_cmd	*create_struct(char ***cmd);
//execute cmd
void	shell_execute(char ***cmd);

char	*rl_gets(char *line_read);

//free every malloc var at the end of every loop
void	end_of_loop(char *line, char ***cmd);

#endif