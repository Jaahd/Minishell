#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int				bi_exit(char **arg, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("bi exit");
	int			i;
	(void)env;
	i = 0;
	if (arg[1] && arg[2])
	{
		ft_putendl("minishell: exit : too many arguments");
		return (-1);
	}
	while(arg[1] && arg[1][i])
	{
		if(ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr("exit : ");
			ft_putstr(arg[1]);
			ft_putendl(": numeric argument required");
			return (-1);
		}
		i++;
	}
	i = (arg[1] ? ft_atoi(arg[1]) : 0);
	free_tab(&arg);
	duo_del(env);
	exit(i);
	return (0);
}
