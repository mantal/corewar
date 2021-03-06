/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 16:12:37 by dlancar           #+#    #+#             */
/*   Updated: 2016/01/12 15:29:20 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

static size_t	get_size(const char **s)
{
	size_t	r;
	int		i;

	r = 0;
	i = 0;
	while (s[i])
		r += ft_strlen(s[i++]);
	return (r);
}

char			*ft_strmerge(const char **s)
{
	char	*res;
	int		i;
	int		j;

	res = ft_malloc(sizeof(char) * get_size(s));
	i = 0;
	j = 0;
	while (s[i])
	{
		ft_memcpy(res + j, s[i], ft_strlen(s[i]));
		j += ft_strlen(s[i]);
		i++;
	}
	return (res);
}
