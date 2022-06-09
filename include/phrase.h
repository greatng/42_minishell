/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:09:57 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/09 21:50:25 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHRASE_H
# define PHRASE_H

# include "minishell.h"

/* ms_check_phrase.c*/
int		is_complete_quote(char *str);
int		is_pipe_error(char *line);
int		is_syntax(char c);
int		check_lexer(char **lexer);

/* ms_check_phrase_2.c*/
int		check_phrase(char *cmd);

/* ms_lexer.c*/
char	**lexer(char *line);

/* ms_parser.c*/
char	***parser(char **lex);

/* ms_free_pharse.c*/
void	free_lexer(char **lex);
void	free_parser(char ***par);

#endif
