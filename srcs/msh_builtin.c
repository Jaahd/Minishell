#include "minishell.h"
#include "libft.h"
#include <stdio.h>

// fonction qui ajoute a env la variable name avec la valeur value
//
// attention si la valeur contient des caracteres non alphanum ca ne marche pas !!!!!
//
// ATTENTION!!!!! : est ce qu'il faut trier par ordre alpha????
int			add_env(t_duo **env, char *name, char *value)
{
	if (DEBUG == 1)
		ft_putendl("add env");
	if (name == NULL)
		return (-1);
	else
		duo_pushback(env, name, value);
	return (0);
}

// fonction qui modifie ou ajoute la variable name avec la valeur value
int			change_env(t_duo **env, char *name, char *value)
{
	t_duo		*cpy;

	cpy = *env;
	while (cpy)
	{
		if (ft_strcmp(cpy->name, name) == 0)
		{
			free(cpy->value);
			cpy->value = ft_strdup(value);
			return (1);
		}
		cpy = cpy->next;
	}
	add_env(env, name, value);
	return (0);
}

// fonction qui suprime de env la variable name
int			del_first(t_duo **env, char *name)
{
	if (DEBUG == 1)
		ft_putendl("del first");
	t_duo		*cpy;
	t_duo		*tmp;

	cpy = *env;
	tmp = NULL;
	if (ft_strcmp(name, cpy->name) == 0)
	{
		tmp = cpy->next;
		ft_strdel(&(cpy->name));
		ft_strdel(&(cpy->value));
		free(cpy);
		cpy = tmp;
		return (1);
	}
	return (0);
}

int			del_env(t_duo **env, char *name)
{
	if (DEBUG == 1)
		ft_putendl("del env");
	t_duo		*cpy;
	t_duo		*tmp;

	if (del_first(env, name) == 1)
		return (1);
	cpy = *env;
	tmp = NULL;
	while (cpy && cpy->next && cpy->next->next)
	{
		if (ft_strcmp(name, cpy->next->name) == 0)
		{
			tmp = cpy->next->next;
			ft_strdel(&(cpy->next->name));
			ft_strdel(&(cpy->next->value));
			free(cpy->next);
			cpy->next = tmp;
			return (1);
		}
		cpy = cpy->next;
	}
	return (-1);
}

// fonction qui renvoie la valeur "value" de la variable "name" de env
char		*get_env(t_duo **env, char *name)
{
	if (DEBUG == 1)
		ft_putendl("get env");
	t_duo		*cpy;

	cpy = *env;
	while (cpy)
	{
		if (ft_strcmp(name, cpy->name) == 0)
			return (cpy->value);
		cpy = cpy->next;
	}
	return (NULL);
}

int			bi_unsetenv(char **arg, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("bi unsetenv");
	int			i;

	i = 1;
	if (!arg[i])
		ft_putendl("minishell: unsetenv: too few arguments.");
	while(arg[i])
	{
		del_env(env, arg[i]);
		i++;
	}
	return (0);
}

int			bi_setenv(char **arg, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("bi setenv");

	if (!arg[1])
	{
		bi_env(arg, env); // heu je dois mettre quoi la????
		return (0);
	}
	if (arg[1] && arg[2] && !arg[3])
	{
		change_env(env, arg[1], arg[2]);
		return (0);
	}
	if (arg[3])
	{
		ft_putendl("minishell: setenv: too many arguments.");
		return (-1);
	}
	return (0);
}

/*
   int			bi_cd(char **arg, t_duo **env)
   {
   if (DEBUG == 1)
   ft_putendl("bi cd");
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
	// free env et arg avant d'exit !!!!!!!
	exit(i);
	return (0);
}

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
	/*		ft_putstr(cpy->name);
			ft_putchar('=');
			ft_putendl(cpy->value);
	*/		cpy = cpy->next;
		}
	}
	return (0);
}
