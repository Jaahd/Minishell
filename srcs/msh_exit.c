/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
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

int				bi_exit(char **arg, t_duo **env)
{
	int			i;

	i = 0;
	if (arg && arg[1] && arg[2])
	{
		ft_putendl("minishell: exit : too many arguments");
		return (-1);
	}
	while (arg && arg[1] && arg[1][i])
	{
		if (ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr("exit : ");
			ft_putstr(arg[1]);
			ft_putendl(": numeric argument required");
			return (-1);
		}
		i++;
	}
	i = (arg && arg[1] ? ft_atoi(arg[1]) : 0);
	ft_putendl("exit");
	free_tab(&arg);
	duo_del(env);
	exit(i);
	return (0);
}
