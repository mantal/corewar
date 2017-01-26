/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:47:26 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/26 18:02:28 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ftio.h>

static int8_t	get_prog_idx(t_process *process)
{
	int8_t i;

	i = 0;
	while (i < (int8_t)process->vm->programs.size)
	{
		if (((t_program*)array_get(&process->vm->programs, i))->id ==
			process->owner->id)
			return (i);
		i++;
	}
	return (-1);
}

void			vm_memread(t_process *process, void *ptr, int pos, size_t size)
{
	char		*target;
	size_t		i;

	i = 0;
	target = ptr;
	while (i < size)
	{
		target[i] = process->entry_point[(pos + i + MEM_SIZE) % MEM_SIZE];
		i++;
	}
}

void			vm_memwrite(t_process *process, void *ptr, int pos,
	int32_t size)
{
	char	*target;
	int32_t	y;
	int32_t	i;

	i = size - 1;
	y = 0;
	target = (char*)ptr;
	while (i >= 0)
	{
		process->entry_point[(pos + y + MEM_SIZE) % MEM_SIZE] = target[i];
		process->vm->memory_owner[(pos + y + MEM_SIZE) % MEM_SIZE] =
			get_prog_idx(process) + 1;
		i--;
		y++;
	}
}

void			process_dump_registers(t_process *process)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
	{
		verbose("0X%X: r%d = %u\n", process->reg + i, i, process->reg[i]);
	}
}
