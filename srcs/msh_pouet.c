#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int			display_prompt(t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("display prompt");
	char		*name;
	char		*path;
	int			i;

	i = 0;
	name = get_env(env, "LOGNAME");
	path = get_env(env, "PWD");
	if (name)
	{
		ft_putstr("\033[32;1m");
		ft_putstr(name);
		ft_putstr(": \033[0m");
	}
	if (path)
	{
		ft_putstr("\033[34;1m");
		ft_putstr(path);
		ft_putstr(" \033[0m");
	}
	ft_putstr("\033[36;1m$> \033[0m");
	return (0);
}

