/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:19:09 by avacher           #+#    #+#             */
/*   Updated: 2016/01/19 22:34:02 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new != NULL)
	{
		new->content_size = 0;
		new->content = NULL;
		new->next = NULL;
		if (content)
		{
			new->content = ft_memalloc(content_size);
			if (new->content == NULL)
				return (new);
			ft_memcpy(new->content, content, content_size);
			new->content_size = content_size;
		}
	}
	return (new);
}
