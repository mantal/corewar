/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:00:22 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/26 18:38:38 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include "vm.h"

static char	*get_color2(t_vm *vm, int pos)
{
	if (vm->memory_owner[pos] == 0)
		return ("\x1B[37m");
	else
	{
		if (vm->memory_owner[pos] - 1 >= (int)vm->programs.size)
			return (get_color(vm->memory_owner[pos]));
		else
			return (((t_program*)array_get(&vm->programs,
				vm->memory_owner[pos] - 1))->color);
	}
}

void		vm_dump(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("\n0x%x   : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%s", get_color2(vm, i));
		ft_printf("%s%x\x1B[0m\x1B[22m ", vm->memory[i] > 15 ? "" : "0",
			vm->memory[i]);
		if (!((i + 1) % 64) && i + 1 < MEM_SIZE)
		{
			if (i < 256)
				ft_printf("\n0x%x  : ", i + 1);
			else
				ft_printf("\n0x%x : ", i + 1);
		}
		i++;
	}
}
