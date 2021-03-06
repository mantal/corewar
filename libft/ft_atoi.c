/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 15:27:06 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/09 17:47:44 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "libft.h"

static char		*skip_white_space(const char *s)
{
	while (s && ft_isspace(*s))
		s++;
	return ((char*)s);
}

static char		*skip_nul(const char *s)
{
	char	*str;

	str = (char*)s;
	while (*str == '0')
		str++;
	return (str);
}

static size_t	get_size(const char *s)
{
	size_t	i;

	i = 0;
	while (ft_isdigit((int)s[i]))
		i++;
	return (i);
}

/*
** TODO: CLEAN THIS SHIT
*/

int				ft_atoi(const char *str)
{
	long long	result;
	int			neg;
	size_t		size;
	char		*s;

	neg = 1;
	result = 0;
	s = skip_white_space(str);
	if (!s)
		return (0);
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		s++;
		neg = -1;
	}
	s = skip_nul(s);
	size = get_size(s);
	while (ft_isdigit((int)*s))
	{
		result += (*s - '0') * ft_pow(10, size-- - 1);
		s++;
	}
	return (result * neg);
}
