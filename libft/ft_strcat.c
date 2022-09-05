#include "../minishell.h"

char	*my_strcat(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst + strlen(dst);
	while (*src != '\0')
	{
		ptr++ = src++;
	}
	*ptr = '\0';
	return (dst);
}
