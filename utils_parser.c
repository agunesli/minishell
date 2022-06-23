#include "minishell.h"

int	found_char(char	*read, char c)
{
	int	i;

	i = 0;
	if (!read)
		return (-1);
	while (read[i])
	{
		if (read[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int     ft_min(int x, int y, int z)
{
        int     min1;
        int     min2;
        int     min3;

        if (x != -1 && y != -1 && z != -1)
        {
                if (x < y && x < z)
                        return (x);
                else
                        return (ft_min(y, z, x));
        }
        else if (x == -1)
        {
                if (y < z)
                        return (y);
                else
                        return (z);
        }
        else
                return (ft_min(y, z, x));
}
