/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 18:06:15 by avacher           #+#    #+#             */
/*   Updated: 2016/04/05 18:06:15 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static int		del_first(t_duo **env, char *name)
{
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
		*env = tmp;
		return (1);
	}
	return (0);
}

static int		del_env(t_duo **env, char *name)
{
	t_duo		*cpy;
	t_duo		*tmp;

	if (del_first(env, name) == 1)
		return (1);
	cpy = *env;
	tmp = NULL;
	while (cpy && cpy->next)
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

int				bi_unsetenv(char **arg, t_duo **env)
{
	int			i;

	i = 1;
	if (!arg[i])
		ft_putendl("minishell: unsetenv: too few arguments.");
	while (arg[i])
	{
		if (del_env(env, arg[i]) == -1)
		{
			ft_putstr("minishell: unsetenv: '");
			ft_putstr(arg[i]);
			ft_putendl("': undefined variable");
		}
		i++;
	}
	return (0);
}
