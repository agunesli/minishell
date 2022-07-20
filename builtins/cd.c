#include "../minishell.h"

/* first case : relative paths */
/* second case : no backslash */
/* third case : correct format */

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*s3;
// 	int		len;
// 	int		i;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return ((char *)s2);
// 	if (!s2)
// 		return ((char *)s1);
// 	i = 0;
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	s3 = (char *)malloc(len + 1);
// 	if (!s3)
// 		return (NULL);
// 	while (*s1)
// 		*(s3 + i++) = *(char *)s1++;
// 	while (*s2)
// 		*(s3 + i++) = *(char *)s2++;
// 	*(s3 + i) = '\0';
// 	return (s3);
// }

void
cd_error(char *str)
{
	fprintf(stderr, "bash: cd: %s: No such file or directory", str);
}

int
ft_cd_handler(char *dst, int x)
{
	/* Tu dois update tes vars denv avec le old path sur OLDPWD, des le debut, puisque si x == 1, old_pwd sera modif */
	char old_pwd[4096];
	char *final_path = NULL;
	int rtvl = 0;

	getcwd(old_pwd, sizeof(old_pwd));
	if (x == 0)
	{
		final_path = ft_strjoin(getenv("HOME"), dst + 1);
	}
	else if (x == 1)
	{
		strcat(old_pwd, "/");
		strcat(old_pwd, dst);
		final_path = strdup(old_pwd);
	}
	else
	{
		final_path = strdup(dst);
	}
	if (chdir(final_path) == -1)
	{
		cd_error(dst);
		rtvl = -1;
	}
	free(final_path);
	free(dst);
	return rtvl;
}

int
ft_cd(char **cmd, t_data *my_data)
{
	char	*dst_path;
	char	actual[4096];
	int 	rtvl;

	(void)my_data;
	if (cmd[1] == NULL)
	{
		return -1;
	}
	dst_path = strdup(cmd[1]);
	if (dst_path[0] == '~') // relative path
	{
		rtvl = ft_cd_handler(dst_path, 0);
	}
	else if (dst_path[0] != '/') // no backslash
	{
		rtvl =  ft_cd_handler(dst_path, 1);
	}
	else // correct format
	{
		rtvl = ft_cd_handler(dst_path, 2);
	}
	printf("ACTUAL POS : %s \n", getcwd(actual, sizeof(actual)));
	return rtvl;
}