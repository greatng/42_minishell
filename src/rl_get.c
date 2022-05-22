/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:18:26 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/22 17:30:25 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*rl_gets (char *line_read)
{
	line_read = readline (GREEN "minihell" RES RED" § " RES);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}