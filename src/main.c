#include "../include/minishell.h"

int main()
{
	char	*cmd;
	char	**lex;
	char	*buf;
	char	***cmd_split;

	shell_signal();
	while (1)
	{
		buf = malloc(sizeof(char) * (256));
		cmd = readline(GREEN "minihell" RES RED" § " RES);
		if (!cmd)
			continue;
		lex = lexer(cmd);
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
		}
		free(buf);
		free(cmd);
	}
	return 0;
}

// Need to compare if cmd is built in fn
// if it is, then call function. If not then call execve