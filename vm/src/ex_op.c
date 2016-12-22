/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:28:27 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/22 16:48:54 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "program.h"
#include <ftio.h>
#include <ftendianess.h>


//TODO les params doivent etre cast en 8/16/32 quand besoin sinon ils risaue ecrire trop loin


void	write_32(const void *src, void *dst)
{
	ft_memcpy(dst, src, 2);
	swap_uint32(dst);
}

void op_live(t_vm *vm, t_process *process, int32_t *args[3])
{
	(void)vm;
	(void)process;
	(void)args;
	info("[%d]: live %d\n", process->pid, *args[0]);
}

void op_ld(t_vm *vm, t_process *process, int32_t *args[3])
{

}

void op_st(t_vm *vm, t_process *process, int32_t *args[3])
{
	(void)vm;
	info("[%d]: st %d 0x%x\n", process->pid, *args[0], args[1]);
	write_32(args[0], args[1]);
	//*args[1] = *args[0];
	process->carry = *args[1] == 0;
}

//TODO LE CARRY DOIT ETRE RESET

void op_add(t_vm *vm, t_process *process, int32_t *args[3])
{
	*args[2] = *args[0] + *args[1];
    process->carry = *args[2] == 0;
}

void op_sub(t_vm *vm, t_process *process, int32_t *args[3])
{
    process->reg[args[3][2]] = process->reg[args[3][0]] - process->reg[args[3][1]];
    process->carry = process->reg[args[3][2]] == 0;
}

void op_and(t_vm *vm, t_process *process, int32_t *args[3])
{
    process->reg[args[3][2]] = process->reg[args[3][0]] & process->reg[args[3][1]]; 
    process->carry = process->reg[args[3][2]] == 0;
}

void op_or(t_vm *vm, t_process *process, int32_t *args[3])
{
    process->reg[args[3][2]] = process->reg[args[3][0]] | process->reg[args[3][1]]; 
    process->carry = process->reg[args[3][2]] == 0;
}

void op_xor(t_vm *vm, t_process *process, int32_t *args[3])
{
    process->reg[args[3][2]] = process->reg[args[3][0]] ^ process->reg[args[3][1]]; 
    process->carry = process->reg[args[3][2]] == 0;
}

void op_zjmp(t_vm *vm, t_process *process, int32_t *args[3])
{
	if (process->carry)
		process->pc += *args[0];
}

void op_ldi(t_vm *vm, t_process *process, int32_t *args[3])
{

}

void op_sti(t_vm *vm, t_process *process, int32_t *args[3])
{

}

void op_fork(t_vm *vm, t_process *process, int32_t *args[3])
{

}

void op_lld(t_vm *vm, t_process *process, int32_t *args[3])
{

}

void op_lldi(t_vm *vm, t_process *process, int32_t *args[3])
{

}

void op_lfork(t_vm *vm, t_process *process, int32_t *args[3])
{

}

void op_aff(t_vm *vm, t_process *process, int32_t *args[3])
{

}
