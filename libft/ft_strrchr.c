/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 16:38:06 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/02 18:11:40 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*target;

	target = NULL;
	if (!s)
		return ((char*)target);
	while (*s)
	{
		if (*s == c)
			target = s;
		s++;
	}
	if (!c)
		target = s;
	return ((char*)target);
}
