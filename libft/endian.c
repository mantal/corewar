/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 18:32:10 by tguillem          #+#    #+#             */
/*   Updated: 2017/01/03 20:00:32 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				is_le(void)
{
	unsigned int		x;

	x = 1;
	return ((int)(((char *)&x)[0]));
}

int				is_be(void)
{
	return (!is_le());
}

unsigned short	swap_ushort(unsigned short lt)
{
	return ((lt << 8) | (lt >> 8));
}

short			swap_short(short lt)
{
	return ((lt << 8) | ((lt >> 8) & 0xFF));
}

unsigned int	swap_uint(unsigned int lt)
{
	lt = ((lt << 8) & 0xFF00FF00) | ((lt >> 8) & 0xFF00FF);
	return ((lt << 16) | (lt >> 16));
}
