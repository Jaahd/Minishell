#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int			set_env(char ***env, char *name, char *value)
{
	// fonction qui ajoute a env la variable name avec la valeur value
}

int			del_env(char ***env, char *name)
{
	// fonction qui suprime de env la variable name
}

char		*get_env(char ***env, char *name)
{
	char		*value;
	// fonction qui renvoie la valeur 'value' de la variable 'name'
	return (value);
}

/*
int			bi_cd(char **arg, char **env)
{
	if (DEBUG == 1)
		ft_putendl("bi cd");
	return (0);
}

int			bi_setenv(char **arg, char ***env)
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
int			bi_exit(char **arg, char ***env)
{
	if (DEBUG == 1)
		ft_putendl("bi exit");
	int			i;
(void)env;
	i = 0;
	if (arg[1] && arg[2])
	{
		ft_putendl("exit : too many arguments");
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
	/*free_tab(env);
	*/i = (arg[1] ? ft_atoi(arg[1]) : 0);
	exit(i);
	return (0);
}

int			bi_env(char **arg, char ***env)
{
	if (DEBUG == 1)
		ft_putendl("bi env");
	int			i;

	i = 0;
	if (arg[1])
	{
		ft_putstr("env :");
		ft_putstr(arg[1]);
		ft_putendl(": No such file or directory");
		return (-1);
	}
	while (env[i])
	{
		ft_putendl((*env)[i]);
		i++;
	}
	return (0);
}
