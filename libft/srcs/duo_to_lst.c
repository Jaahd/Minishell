/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duo_to_lst.c                                       :+:      :+:    :+:   */
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

static t_duo		*duo_new(char *name, char *value)
{
	t_duo			*new;

	if ((new = (t_duo *)malloc(sizeof(t_duo))) == NULL)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	if (name == NULL && value == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	return (new);
}

static int			duo_pushback(t_duo **lst, char *name, char *value)
{
	t_duo			*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = duo_new(name, value);
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = duo_new(name, value);
	return (0);
}

t_duo				*tbl_to_lst(char **tbl, char c)
{
	int				i;
	char			*tmp_name;
	char			*tmp_value;
	t_duo			*lst;

	i = 0;
	while (tbl[i])
	{
		tmp_name = ft_strsub();
		duo_pushback(&lst,, strchr_1(tbl[î], '='));
	}
	return (lst);
}
