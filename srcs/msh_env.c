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

int			bi_env(char **arg, t_duo **env)
{
	t_duo		*cpy;

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
