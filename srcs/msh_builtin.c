#include "minishell.h"
#include "libft.h"
#include <stdio.h>
/*
int			set_env(char ***env, char *name, char *value)
{
	if (DEBUG == 1)
		ft_putendl("set env");
	// fonction qui ajoute a env la variable name avec la valeur value
}

int			del_env(char ***env, char *name)
{
	if (DEBUG == 1)
		ft_putendl("del env");
	int			i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	len = ft_strlen(name);
	while ((*env)[i])
	{
		tmp = ft_strsub((*env)[i], 0, len);
		if (ft_strcmp(name, tmp) == 0)
		{
		}
		i++;
	}
	printf("value : %s\n", value);
	{
		
	}
	// fonction qui suprime de env la variable name
}
*/
char		*get_env(char ***env, char *name)
{
	if (DEBUG == 1)
		ft_putendl("get env");
	char		*value;
	char		*tmp;
	int			i;
	int			len;

	i = 0;
	tmp = NULL;
	value = NULL;
	len = ft_strlen(name);
	while ((*env)[i])
	{
		tmp = ft_strsub((*env)[i], 0, len);
		if (ft_strcmp(name, tmp) == 0)
		{
			value = ft_strsub((*env)[i], len, ft_strlen((*env)[i]));
		}
		i++;
	}
	printf("value : %s\n", value);
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
   int			ime;

   while (env[i])
   {
   if (env[i] == arg[1])
   {

   }
   }
   return (0);
   }
   */
int			bi_exit(char **arg, t_duo **env)
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
	i = (arg[1] ? ft_atoi(arg[1]) : 0);
	exit(i);
	return (0);
}

int			bi_env(char **arg, t_duo **env)
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
	else
	{
		while (env)
		{
			ft_putstr((*env)->name);
			ft_putchar('=');
			ft_putendl((*env)->value);
			(*env) = (*env)->next;
		}
	}
	return (0);
}
