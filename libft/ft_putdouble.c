/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 11:50:42 by dlancar           #+#    #+#             */
/*   Updated: 2016/01/09 17:02:31 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"

void	ft_putdouble(double d)
{
	ft_putdouble_fd(STDOUT, d);
}
