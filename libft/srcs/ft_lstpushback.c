/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 13:41:00 by avacher           #+#    #+#             */
/*   Updated: 2015/11/28 18:12:57 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **alst, char *content)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
		tmp = tmp->next;
	tmp = ft_lstnew(content);
}
