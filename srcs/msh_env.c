#include "minishell.h"
#include "libft.h"

// ajouter la gestion de env -i (donc avec qqch derriere env ^^), enventuellement ac -u...
int			bi_env(char **arg, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("bi env");
	t_duo		*cpy;
	int			i;

	i = 0;
	cpy = *env;
	if (arg[1])
 	{
		ft_putstr("env :");
		ft_putstr(arg[1]);
		ft_putendl(": No such file or directory");
		return (-1);
	}
	else
	{
		while (cpy)
		{
			ft_putstr(cpy->name);
			ft_putchar('=');
			ft_putendl(cpy->value);
			cpy = cpy->next;
		}
	}
	return (0);
}
