/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 18:06:15 by avacher           #+#    #+#             */
/*   Updated: 2016/04/05 18:06:15 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int		print_modified_env(char **arg, t_duo **env)
{
	t_duo		*cpy;
	int			i;

	cpy = *env;
	i = 0;
	if (arg[1] && arg[2])
		return (-1);
	while (arg[1] && arg[1][i])
	{
		if (arg[1][i] == '=')
			break ;
		i++;
	}
	if (arg[1] && arg[1][i] == '\0')
		return (-1);
	while (cpy)
	{
		ft_putstr(cpy->name);
		ft_putchar('=');
		ft_putendl(cpy->value);
		cpy = cpy->next;
	}
	ft_putendl(arg[1]);
	return (0);
}

int				bi_env(char **arg, t_duo **env)
{
	t_duo			*cpy;

	cpy = *env;
	if (arg[1])
	{
		if (print_modified_env(arg, env) == -1)
		{
			ft_putstr("env :");
			ft_putstr(arg[1]);
			ft_putendl(": No such file or directory");
			return (-1);
		}
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
