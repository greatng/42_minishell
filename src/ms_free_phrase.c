/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_phrase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:06:23 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/17 21:14:17 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phrase.h"

void	free_lexer(char **lex)
{
	int	i;

	i = 0;
	while (lex && lex[i])
	{
		free(lex[i]);
		i++;
	}
	if (lex)
		free(lex);
}

void	free_parser(char ***par)
{
	int	i;
	int	j;

	i = 0;
	while (par[i])
	{
		j = 0;
		while (par[i][j])
		{
			free(par[i][j]);
			j++;
		}
		free(par[i]);
		i++;
	}
	free(par);
}
