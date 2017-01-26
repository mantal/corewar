/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 16:50:13 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/26 18:00:22 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	*get_color(size_t index)
{
	if (index == 0)
		return ("\x1B[31m");
	if (index == 1)
		return ("\x1B[32m");
	if (index == 2)
		return ("\x1B[33m");
	if (index == 3)
		return ("\x1B[34m");
	else
		return ("\x1B[36m");
}

void		assign_colors(t_vm *vm)
{
	size_t i;

	i = 0;
	while (i < vm->programs.size)
	{
		((t_program*)array_get(&vm->programs, i))->color = get_color(i);
		i++;
	}
}
