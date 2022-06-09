/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/09 21:44:54 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"

/* ms_quote_utils.c */
char	*get_envname(char *str);
char	*ft_getenv(char *name, char **env);

/* ms_quote_utils_2.c */
int		find_quote(char *str);
char	*unquote(char *command);
char	*ft_append(char *buffer, char c);
char	*ft_join(char *front, char *back);
char	*ft_append_env(char *buffer, char *command, int *index);

/* ms_translate_vars.c */
char	*translate_cmd(char *command);

#endif
