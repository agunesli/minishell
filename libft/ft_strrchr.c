#include "../minishell.h"

char    *ft_strrchr(const char *s, int c)
{
    int    i;

    i = ft_strlen(s);
    if (s[i] == (char)c)
        return ((char *)(s + i));
    while (i > -1)
    {
        if (s[i] == (char)c)
            return ((char *)(s + i));
        i--;
    }
    return (NULL);
}