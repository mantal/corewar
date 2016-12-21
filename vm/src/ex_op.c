/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:28:27 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/20 15:56:02 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_live(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_ld(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_st(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_add(t_vm *vm, t_process *process, uint32_t *args[3])
{
    process->reg[args[2]] = process->reg[args[0]] + process->reg[args[1]];
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_sub(t_vm *vm, t_process *process, uint32_t *args[3])
{
    process->reg[args[2]] = process->reg[args[0]] - process->reg[args[1]];
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_and(t_vm *vm, t_process *process, uint32_t *args[3])
{
    process->reg[args[2]] = process->reg[args[0]] & process->reg[args[1]]; 
    process->carry = process->reg[args[2]] == 0 ? 1 : 0; 
}

void op_or(t_vm *vm, t_process *process, uint32_t *args[3])
{
    process->reg[args[2]] = process->reg[args[0]] | process->reg[args[1]]; 
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_xor(t_vm *vm, t_process *process, uint32_t *args[3])
{
    process->reg[args[2]] = process->reg[args[0]] ^ process->reg[args[1]]; 
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_zjmp(t_vm *vm, t_process *process, uint32_t *args[3])
{
}

void op_ldi(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_sti(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_fork(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_lld(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_lldi(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_lfork(t_vm *vm, t_process *process, uint32_t *args[3])
{

}

void op_aff(t_vm *vm, t_process *process, uint32_t *args[3])
{

}
