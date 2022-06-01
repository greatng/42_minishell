/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:35:28 by pngamcha          #+#    #+#             */
/*   Updated: 2022/06/01 10:33:28 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	static char	*line_read = NULL;
	char		**lex;
	char		***cmd_split;
	t_cmd		*tab_cmd;
	//char		test[1024];

	shell_init(argc, argv, env);
	while (1)
	{
		line_read = rl_gets(line_read);
		if (!line_read)
			shell_exit();
		lex = lexer(line_read);
		cmd_split = parser(lex);
		tab_cmd = create_struct(cmd_split);
		// for (size_t i = 0; i < tab_cmd->size; i++)
		// {
		// 	for (int j = 0; tab_cmd[i].cmd[j]; j++)
		// 		printf("%s ", tab_cmd[i].cmd[j]);
		// 	printf("infile = %d outfile = %d \n", tab_cmd[i].infile, tab_cmd[i].outfile);
		// 	read(tab_cmd[i].infile, test, 1024);
		// 	printf("From Here_doc :\n%s", test);
		// }
		// shell_execute(cmd_split);
		// end_of_loop(line_read, cmd_split);
	}
	return (0);
}

//don't forget to free cmd_split
