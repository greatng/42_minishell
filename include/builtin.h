/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:52:24 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/19 00:33:01 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define CLEAR_SCRN "\033[2J \033[H"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define RES "\033[0m"

# include "minishell.h"

void	change_dir(char *dir);
void	present_wd(void);
void	shell_echo(char *str);
void	shell_exit(void);

//Additional function for better usage won't hurt XD

void	shell_ls(void);
void	shell_clear(void);

#endif