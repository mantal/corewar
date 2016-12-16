/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:48:17 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/16 15:50:25 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftendianess.h"
#include <stdint.h>

void		swapInt32(uint32_t *i)
{
	*i = (((*i >> 24) & 0xff)
				| ((*i << 8) & 0xff0000)
				| ((*i >> 8) & 0xff00)
				| ((*i << 24) & 0xff000000));
}
