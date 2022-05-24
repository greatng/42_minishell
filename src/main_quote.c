//Obsolete


#include <string.h>
#include "../include/quote.h"

t_mini g_mini;

int	main(int argc, char **argv, char **envp)
{
	g_mini.env = envp;
	char *c = (char*)malloc(sizeof(char) * 100);
    // test here
	strcpy(c, "\"\'$PATH\'\"");
	printf("%s \n", c);

	char *buffer;
	buffer = translate_cmd(c);
	printf("%s \n", buffer);
	free(buffer);

	return (0);	
}
