/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:40:26 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 16:26:17 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "program.h"
#include <fterror.h>
#include <ftendianess.h>
#include <stdint.h>
#include <ftio.h>

uint8_t		get_param_size(t_op *op, uint8_t pcode)
{
	if (pcode == REG_CODE)
		return (1);
	else if ((pcode == DIR_CODE && op->has_idx) || (pcode == IND_CODE))
		return (IND_DATA_SIZE);
	else if (pcode == DIR_CODE && !op->has_idx)
		return (DIR_DATA_SIZE);
	warning("Invalid pcode %x\n", pcode);
	return (0);
}

void		get_param_pcode(uint8_t raw_data, uint8_t pcodes[4])
{
	int		i;

	i = 4;
	while (--i >= 0)
	{
		pcodes[i] = raw_data % 4;
		raw_data >>= 2;
	}
}

void		swap_uint16(uint16_t *n)
{
	*n = (uint16_t)((*n >> 8) | (*n << 8));
}

void		vm_read(t_process *process, void *p, size_t size)
{
	debug("[%u]        Read %d bytes at position 0x%X", process->pid, size,
					process->entry_point + process->position);
	if (size == 0)
	{
		debug("\n");
		return ;
	}
	vm_memread(process, p, process->position, size);
	if (size == 2)
	{
		swap_uint16(p);
		debug(" raw data = 0x%X\n", *((uint16_t*)p));
	}
	else if (size == 4)
	{
		swap_uint32(p);
		debug(" raw data = 0x%X\n", *((uint32_t*)p));
	}
	else
		debug(" raw data = 0x%X\n", *((uint8_t*)p));
	process->position += size;
}

int32_t		vm_get_param(t_process *process, t_op *op, uint8_t pcode)
{
	int32_t	temp;

	temp = 0;
	debug("[%u]>>  Reading parameter size\n", process->pid);
	vm_read(process, &temp, get_param_size(op, pcode));
	return (temp);
}
