#include "minishell.h"
#include "libft.h"
#include <stdio.h>
/*
int			bi_cd(char **arg, char **env)
{
	if (DEBUG == 1)
		ft_putendl("bi cd");
	return (0);
}

int			bi_setenv(char **arg, char **env)
{
	if (DEBUG == 1)
		ft_putendl("bi setenv");
	return (0);
}

int			bi_unsetenv(char **arg, char **env)
{
	if (DEBUG == 1)
		ft_putendl("bi unsetenv");
	int			i;

	while (env[i])
	{
		if (env[i] == arg[1])
		{

		}
	}
	return (0);
}
*/
int			bi_exit(char **arg, char **env)
{
	if (DEBUG == 1)
		ft_putendl("bi exit");
	if (arg)
	(void)env;
	exit(EXIT_SUCCESS);
	return (0);
}

int			bi_env(char **arg, char **env)
{
	printf("pouet\n");
	if (DEBUG == 1)
		ft_putendl("bi env");
	int			i;
	int			size;

	i = 0;
	size = tbl_len(arg);
	if (size > 1)
		ft_putendl_fd("too many arguments", 2);
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
	return (0);
}
