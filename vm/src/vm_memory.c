/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:47:26 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 17:27:36 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ftio.h>

void	vm_memread(t_process *process, void *ptr, int pos, size_t size)
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

void	vm_memwrite(t_process *process, void *ptr, int pos, int32_t size)
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
		i--;
		y++;
	}
}

void	vm_dump(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("\n0x%x : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%c%x ", vm->memory[i] > 15 ? 0 : '0', vm->memory[i]);
		if (!((i + 1) % 64))
			ft_printf("\n0x%x : ", i);
		i++;
	}
}

void	process_dump_registers(t_process *process)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
	{
		ft_printf("0X%X: r%d = %u\n", process->reg + i, i, process->reg[i]);
	}
}
