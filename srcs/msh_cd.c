#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int			bi_exit(char **arg, char **env)
{
	(void)arg;
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
