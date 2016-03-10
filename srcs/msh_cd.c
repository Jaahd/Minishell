#include <unistd.h>
#include "minishell.h"
#include "libft.h"

int			cd_usage(char **arg)
{
	if (arg[2])
	{
		ft_putendl("cd: Too many arguments.");
		return (-1);
	}
	if (arg[1][0] == '-' && arg[1][1])
	{
		ft_putstr("minishell: cd: -");
		ft_putchar(arg[1][1]);
		ft_putendl(": invalide option\ncd: usage: cd [dir]");
		return (-1);
	}
	return (0);
}

int			cd_access(char **arg)
{
	if (chdir(arg[1]) == -1)
	{
		ft_putstr("minishell: cd: ");
		ft_putstr(arg[1]);
		if ((access(arg[1], F_OK)) == -1)
			ft_putendl(": Permission denied");
		else
			ft_putendl(": No such file or directory");
		return (-1);
	}
	return (0);
}

int			bi_cd(char **arg, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("bi cd");
	char		tmp_pwd;
	// var tmp pour sauvegarger le pwd actuel avant de verifier s'il faut effectivement le changer ou pas

	cd_usage(arg);
	cd_access(arg);

	return (0);
}
