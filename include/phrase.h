/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:09:57 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 12:11:26 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHRASE_H
# define PHRASE_H

# include "minishell.h"

/* 1_phrase_utils.c*/
int		able_to_phrase(char *str);
int		is_pipe_error(char *line);
int     is_syntax(char c);

/* 2_lexer.c*/
char	**lexer(char *line);

/* 3_parser.c*/
char	***parser(char **lex);

/* 4_free_pharse.c*/
void	free_lexer(char **lex);
void	free_parser(char ***par);

#endif
