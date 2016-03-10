#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int			display_prompt(char **env)
{
	if (DEBUG == 1)
		ft_putendl("display prompt");
	char		*name;
	char		*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	name = NULL;
	while (env[i])
	{
		tmp = ft_strsub(env[i], 0, 7);
		if (ft_strcmp("LOGNAME", tmp) == 0)
		{
			name = srch_value(env[i], '=');
			break ;
		}
		i++;
	}
	ft_putstr("\033[34m");
	if (name)
		ft_putstr(name);
	else
		ft_putchar('$');
	ft_putstr("> \033[0m");
	return (0);
}

