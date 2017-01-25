/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:07:44 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 14:09:57 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>
#include <stdint.h>
#include <limits.h>

intmax_t	bigatoi(const char *str)
{
	bool		negate;
	intmax_t	rtn;
	intmax_t	i;

	rtn = 0;
	i = 0;
	negate = false;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		negate = true;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		rtn *= 10;
		if (negate)
			rtn -= str[i] - 48;
		else
			rtn += str[i] - 48;
		i++;
	}
	return (rtn);
}

bool		is_valid_number(const char *nbr)
{
	int			i;
	intmax_t	tmp;

	i = 0;
	if (nbr[0] == '-' && ft_strlen(nbr) >= 11)
		return (false);
	if (nbr[0] != '-' && ft_strlen(nbr) >= 10)
		return (false);
	tmp = bigatoi(nbr);
	if (tmp > INT_MAX || tmp < INT_MIN)
		return (false);
	while (nbr[i])
	{
		if ((nbr[i] >= '0' && nbr[i] <= '9') || (i == 0 && nbr[0] == '-'))
		{
			i++;
			continue ;
		}
		else
			return (false);
	}
	return (true);
}
