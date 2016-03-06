/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbl_to_duo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 10:47:52 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 12:01:07 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*chr_begining(const char *str, int c)
{
	int				i;
	char			*ret;

	i = 0;
	while (str[i] != c)
		i++;
	ret = ft_strsub(str, 0, i);
	return (ret);
}

static char			*strchr_1(const char *str, int c)
{
	while (str && (*str != c) && (*str != '\0'))
		str++;
	if (!str || *str != c)
		return (NULL);
	return ((char*)(str + 1));
}

t_duo				*tbl_to_duo(char **tbl, char c)
{
	int				i;
	char			*tmp_name;
	char			*tmp_value;
	t_duo			*lst;
	i = 0;
	while (tbl[i])
	{
		tmp_name = chr_begining(tbl[i], c);
		tmp_value = strchr_1(tbl[i], c);
		duo_pushback(&lst, tmp_name, tmp_value);
ft_putendl("lolilol");
	}
	return (lst);
}
