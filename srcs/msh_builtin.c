/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 18:06:14 by avacher           #+#    #+#             */
/*   Updated: 2016/04/05 18:06:14 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

// ATTENTION!!!!! : est ce qu'il faut trier par ordre alpha????

// fonction qui ajoute a env la variable name avec la valeur value
int				add_env(t_duo **env, char *name, char *value)
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
int				change_env(t_duo **env, char *name, char *value)
{
	if (DEBUG == 1)
		ft_putendl("change env");
	t_duo			*cpy;

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
	free(cpy);
	return (0);
}

// fonction qui renvoie la valeur "value" de la variable "name" de env
char			*get_env(t_duo **env, char *name)
{
	if (DEBUG == 1)
		ft_putendl("get env");
	t_duo			*cpy;

	cpy = *env;
	while (cpy)
	{
		if (ft_strcmp(name, cpy->name) == 0)
			return (ft_strdup(cpy->value));
		cpy = cpy->next;
	}
	free(cpy);
	return (NULL);
}

int				handle_builtin(char **cmd, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("handle builtin");
	static char		*builtin[] = {"cd", "setenv", "unsetenv", "env", "exit"};
	static int		(*fct_tbl[])(char **cmd, t_duo **env) = {&bi_cd,
						&bi_setenv, &bi_unsetenv, &bi_env, &bi_exit};
	int				i;

	i = 0;
	while (i < 5 && ft_strcmp(cmd[0], builtin[i]) != 0)
		i++;
	if (i < 5 && ft_strcmp(cmd[0], builtin[i]) == 0)
	{
		if (fct_tbl[i](cmd, env) == -1)
			return (-1);
		else
			return (1);
	}
	return (0);
}
