/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:52:24 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 17:08:22 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//builtin fn
void	change_dir(char *dir);
void	present_wd(void);
void	shell_echo(char **echo);
void	shell_exit(void);
void	print_env(char **cmd);
void	shell_export(char **cmd);
void	shell_unset(char **cmd);

//Additional function for better usage won't hurt XD

void	shell_ls(void);
void	shell_clear(void);

//builtin utils
int		check_var_dup(char *cmd);
int		is_var_valid(char *cmd);
size_t	strlen_equal(char *str);
char	*add_equal(char *cmd);

#endif