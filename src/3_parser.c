#include "../include/phrase.h"

static int	count_row(char **lex)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (lex[i])
	{
		if (!ft_strncmp(lex[i], "|", 2))
			count++;
		i++;
	}
	return (++count);
}

static int	count_col(char **lex, int index)
{
	int		i;

	i = 0;
	while (lex[index + i] && ft_strncmp(lex[index + i], "|", 2))
	{
		i++;
	}
	return (i);
}

static char *ft_dup(char *str)
{
    char    *dup;
    int     i;

    dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = 0;
    return (dup);
}

static char **put_row(char **lex, int i_lex)
{
    char    **put;
    int     i;

    put = (char **)malloc(sizeof(char *) * (count_col(lex, i_lex) + 1));
    if (!put)
        return (NULL);
    i = 0;
    while (i < count_col(lex, i_lex))
    {
        put[i] = ft_dup(lex[i_lex + i]);
        i++;
    }
    put[i] = 0;
    return (put);
}

char    ***parser(char **lex)
{
    int     i;
    int     j;
    char    ***pars;

    i = 0;
    j = 0;
    pars = (char ***)malloc(sizeof(char **) * (count_row(lex) + 1));
    if (!pars)
        return (NULL);
    while (lex[i])
    {
        pars[j++] = put_row(lex, i);
        i += count_col(lex, i);
        if (lex[i])
        {
            if (!lex[i + 1])
                pars[j++] = put_row(lex, i);
            i++;
        }
    }
    pars[j] = 0;
    free_lexer(lex);
    return (pars);
}