/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 16:50:13 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/26 18:37:59 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char		*get_color(size_t index)
{
	if (index == 0)
		return ("\x1B[1m\x1B[31m");
	if (index == 1)
		return ("\x1B[1m\x1B[32m");
	if (index == 2)
		return ("\x1B[1m\x1B[33m");
	if (index == 3)
		return ("\x1B[1m\x1B[34m");
	if (index == 4)
		return ("\x1B[31m");
	if (index == 5)
		return ("\x1B[32m");
	if (index == 6)
		return ("\x1B[33m");
	if (index == 7)
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

void		default_color(int i, t_vm *vm, int spacing, int size)
{
	int j;

	j = spacing;
	while (j < spacing + size)
	{
		vm->memory_owner[j] = (int8_t)i + 4;
		j++;
	}
}
