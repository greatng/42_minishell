/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:35:28 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/25 17:11:15 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	static char	*line_read = NULL;
	char		**lex;
	char		***cmd_split;

	convert_arg(argc, argv, env);
	shell_signal();
	while (1)
	{
		line_read = rl_gets(line_read);
		if (!line_read)
			shell_exit();
		lex = lexer(line_read);
		cmd_split = parser(lex);
		convert_var(cmd_split);
		shell_execute(cmd_split);
		end_of_loop(line_read, cmd_split);
	}
	return (0);
}

//don't forget to free cmd_split
