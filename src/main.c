/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:35:28 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/16 20:28:35 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	static char	*line_read = NULL;
	t_cmd		*tab_cmd;

	shell_init(argc, argv, env);
	while (1)
	{
		disable_echo();
		line_read = rl_gets(line_read);
		if (!line_read)
			shell_exit();
		if (ft_strlen(line_read) && check_phrase(line_read))
		{
			tab_cmd = create_struct(parser(lexer(line_read)));
			free(line_read);
			enable_echo();
			shell_execute(tab_cmd);
			end_of_loop(tab_cmd);
		}
		else
			free(line_read);
	}
	return (0);
}
