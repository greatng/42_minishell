/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:16:18 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/10 10:37:02 by pngamcha         ###   ########.fr       */
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

# define NAME1 "  __  _   _     ___                       _  "
# define NAME2 " /__ |_) |_  /\\  |    ()      | | | |\\/| |_) "
# define NAME3 " \\_| | \\ |_ /--\\ |    (_X   \\_| |_| |  | | "

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
	int		infile;
	int		outfile;
	size_t	size;
	char	**cmd;
}	t_cmd;

//Shell initiate, Run only first time
void	shell_init(int argc, char **argv, char **env);
void	disable_echo(void);
void	enable_echo(void);
void	shell_signal(void);
void	convert_arg(int argc, char **argv, char **env);

//Read input
char	*rl_gets(char *line_read);

//Convert output from lexer -> parser > struct
t_cmd	*create_struct(char ***cmd);

//Assign fd to struct
void	struct_fd(t_cmd *cmd, char ***cmd_arr);
//Check if it redirection
int		check_redirection(char *redirect);
//If it's heredoc run this function
int		here_doc(char *delimit);
void	free_heredoc(char *delimit, char *res, char *buf);
//Child signal handler
void	shell_child_signal(void);
//Execute command from struct value
void	shell_execute(t_cmd *tab_cmd);
//If it built in Run cmd and return 1, if it's not return 0
int		run_builtin(char **cmd, t_cmd *tab_cmd);
//Collect child exit status
void	collect_status(int size);

//Find correct path for system command
char	**check_rightcmd(char **cmd, char **path);

//get path from global environment
char	**get_path(void);

//free every malloc var at the end of every loop
void	end_of_loop(t_cmd *tab_cmd);

//clean g_env
int		clean_env(void);

#endif