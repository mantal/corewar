/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:25:44 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:37:28 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int			is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v');
}

static int			first_non_space_char(char *str)
{
	size_t	i;

	i = 0;
	while (is_space(str[i]) || str[i] == '\r' || str[i] == '\f')
		i++;
	return (i);
}

static long int		ft_atoi_rec(long int n, char *str)
{
	if (*str < '0' || *str > '9')
		return (n);
	return (ft_atoi_rec(10 * n + *str - '0', str + 1));
}

long int			ft_atoli(char *str)
{
	if (!str)
		return (0);
	str += first_non_space_char(str);
	if (*str == '-')
		return (-ft_atoi_rec(0, str + 1));
	if (*str == '+')
		return (ft_atoi_rec(0, str + 1));
	return (ft_atoi_rec(0, str));
}
