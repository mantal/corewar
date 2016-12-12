/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 18:32:10 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 18:35:39 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		    	is_le(void)
{
	unsigned int		x;

	x = 1;
	return ((int)(((char *)&x)[0]));
}

int	    		is_be(void)
{
	return (!is_le());
}

short		    swap_short(short lt)
{
	return ((lt << 8) | (lt >> 8));
}

unsigned int 	swap_uint(unsigned int lt)
{
	return (swap_short(lt & 0xffff) << 16) | (swap_short(lt >> 16));
}
