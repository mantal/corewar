/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 16:38:06 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/23 12:59:35 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strnchr(const char *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c && i < n)
		i++;
	return (s[i] == c ? (char*)&s[i] : NULL);
}
