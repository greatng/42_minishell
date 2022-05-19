#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "../include/builtin.h"

int main()
{
	char	*cmd;
	// char	echo1[] = "echo";
	// char	echo2[] = "echo Hello this is echo test";
	// char	echo3[] = "echo     -n This is echo without new line";
	// char	echo4[] = "echo -n";
	// char	echo5[] = "echo -n \'test\'";
	char	*buf;
	char	**cmd_split;
	int	size = 0;

	shell_signal();
	while (1)
	{
		buf = malloc(sizeof(char) * (256));
		cmd = readline(GREEN "minihell" RES RED" § " RES);
		if (!cmd)
			continue;
		cmd_split = ft_split(cmd, ' ');
		while (cmd_split[size])
			size++;
		if (size > 0)
		{
			if (!ft_strncmp("cd", cmd_split[0], 3))
				change_dir(cmd_split[1]);
			if (!ft_strncmp("pwd", cmd_split[0], 4))
				present_wd();
			if (!ft_strncmp("echo", cmd_split[0], 5))
				shell_echo(cmd);
			if (!ft_strncmp("exit", cmd_split[0], 5))
				shell_exit();
			if (!ft_strncmp("ls", cmd_split[0], 3))
				shell_ls();
			if (!ft_strncmp("clear", cmd_split[0], 6))
				shell_clear();
		}
		// shell_echo(echo1);
		// shell_echo(echo2);
		// shell_echo(echo3);
		// shell_echo(echo4);
		// shell_echo(echo5);
		free(buf);
		free(cmd);
	}
	return 0;
}

// Need to compare if cmd is built in fn
// if it is, then call function. If not then call execve