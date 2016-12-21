/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:59:09 by bel-baz           #+#    #+#             */
/*   Updated: 2016/09/29 14:59:34 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushback(t_list *first, void *content, size_t size)
{
	t_list *tmp;

	if (first == NULL)
		return (ft_lstnew(content, size));
	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_lstnew(content, size);
	return (first);
}
