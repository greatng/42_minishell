#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "../include/builtin.h"

int main()
{
	char	*cmd;
	char	echo1[] = "echo";
	char	echo2[] = "echo Hello this is echo test";
	char	echo3[] = "echo     -n This is echo without new line";
	char	echo4[] = "echo -n";
	char	echo5[] = "echo -n \'test\'";
	char	*buf;

	while (1)
	{
		buf = malloc(sizeof(char) * (256));
		cmd = readline("minihell> ");
		//change_dir(cmd);
		//present_wd();
		printf("%s > %s\n", getcwd(buf, 256), cmd);
		shell_echo(echo1);
		shell_echo(echo2);
		shell_echo(echo3);
		shell_echo(echo4);
		shell_echo(echo5);
		free(buf);
		shell_exit();
	}
	return 0;
}

// Need to compare if cmd is built in fn
// if it is, then call function. If not then call execve