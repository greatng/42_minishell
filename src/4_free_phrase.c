#include "../include/phrase.h"

void    free_lexer(char **lex)
{
    int     i;

    i = 0;
    while (lex[i])
    {
        free(lex[i]);
        i++;
    }
    free(lex);
}

void    free_parser(char ***par)
{
    int     i;
    int     j;

    i = 0;
    while (par[i])
    {
        j = 0;
        while (par[i][j])
        {
            free(par[i][j]);
            j++;
        }
        free(par[i]);
        i++;
    }
    free(par);
}