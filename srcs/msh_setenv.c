/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 18:06:15 by avacher           #+#    #+#             */
/*   Updated: 2016/04/05 18:06:15 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int		is_valid(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '/' && str[i] != ':' && str[i] != '-'
				&& str[i] != ',' && ft_isalnum(str[i]) == 0)
		{
			ft_putstr("minishell: setenv: '");
			ft_putstr(str);
			ft_putendl("': not a valid identifier");
			return (-1);
		}
		i++;
	}
	return (0);
}

int				bi_setenv(char **arg, t_duo **env)
{
	int			i;

	i = 0;
	while (arg[i])
	{
		if (is_valid(arg[i]) != 0)
			return (-1);
		i++;
	}
	if (i < 2)
	{
		bi_env(arg, env);
		return (0);
	}
	if (i == 2 || i == 3)
	{
		change_env(env, arg[1], arg[2]);
		return (0);
	}
	if (i > 3)
	{
		ft_putendl("minishell: setenv: too many arguments.");
		return (-1);
	}
	return (0);
}
