/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/05 10:38:47 by dlancar           #+#    #+#             */
/*   Updated: 2016/01/12 15:27:24 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"
#include <stdlib.h>

/*
** Return a new string composed of the concanation of s1 and s2.
** If flag = 1, s1 will be free at the end of the process, if flag = 2 s2 will
** be free, if flag = 3 both string will be freed.
*/

char	*ft_strjoinf(char *s1, char *s2, t_flags flag)
{
	char	*res;

	res = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_bzero(res, sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcat(res, s2);
	if (flag & 1)
		free(s1);
	if (flag & 2)
		free(s2);
	return (res);
}
