#include "../include/minishell.h"

t_mini	g_mini;

int	main(int argc, char **argv, char **env)
{
	static char	*line_read = NULL;
	char	**lex;
	char	***cmd_split;

	convert_arg(argc, argv, env);
	shell_signal();
	while (1)
	{
		line_read = rl_gets(line_read);
		if (!line_read)
			shell_exit();
		lex = lexer(line_read);
		cmd_split = parser(lex);
		for (int i = 0; cmd_split[i]; i++)
		{
			if (!ft_strncmp("cd", cmd_split[i][0], 3))
				change_dir(cmd_split[i][1]);
			else if (!ft_strncmp("pwd", cmd_split[i][0], 4))
				present_wd();
			else if (!ft_strncmp("echo", cmd_split[i][0], 5))
				shell_echo(cmd_split[i]);
			else if (!ft_strncmp("exit", cmd_split[i][0], 5))
				shell_exit();
			else if (!ft_strncmp("ls", cmd_split[i][0], 3))
				shell_ls();
			else if (!ft_strncmp("clear", cmd_split[i][0], 6))
				shell_clear();
			else if (!ft_strncmp("env", cmd_split[i][0], 4))
				print_env(cmd_split[i]);
		}
		free(line_read);
		line_read = NULL;
	}
	return 0;
}

// Need to compare if cmd is built in fn
// if it is, then call function. If not then call execve