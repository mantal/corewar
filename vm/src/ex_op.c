/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:28:27 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/20 17:48:36 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "program.h"
#include <ftio.h>

int		check_param(t_op *op, t_op_data *data)
{
	int		i;

	i = -1;
	while (++i < op->nb_params)
	{
		if ((op->param_types[i] >> (data->param_pcodes[i] - 1)) % 2 == 0)
			return (0);
		if (data->param_pcodes[i] == REG_CODE && data->params[i] > 16)
			return (0);
	}
	return (1);
}

void	dump_int32(int32_t *param, size_t size)
{
	size_t	i;

	i = 0;
	while (++i < size)
	{
		debug("0x%X\n", *(param + i));
	}
	debug("\n");
}

int32_t	*get_register(t_process *process, t_op_data *data, int index)
{
	int32_t		ptype;
	int32_t		param;
	int32_t		pcode;

	ptype = process->current_instruction->param_types[index];
	param = data->params[index];
	pcode = data->param_pcodes[index];
	if ((ptype == T_REG || ((ptype & T_REG) && pcode == REG_CODE)) && param <= REG_NUMBER)
		return ((int32_t *)(process->reg + param));
	else
		return (NULL);
}

int32_t	*get_indirect(t_process *process, t_op_data *data, int index)
{
	int32_t		ptype;
	int32_t		param;
	int32_t		pcode;

	ptype = process->current_instruction->param_types[index];
	param = data->params[index];
	if (process->current_instruction->opcode != 0xA)
		param = param % IDX_MOD;
	pcode = data->param_pcodes[index];
	if (ptype == T_IND || ((ptype & T_IND) && pcode == IND_CODE))
		return ((int32_t *)&process->entry_point[(process->position + param + MEM_SIZE) % MEM_SIZE]);
	else
		return (NULL);
}

int32_t	get_value(t_process *process, t_op_data *data, int index)
{
	int32_t	*tmp;

	if ((tmp = get_register(process, data, index)) || (tmp = get_indirect(process, data, index)))
		return *tmp;
	return data->params[index];
}

void op_live(t_vm *vm, t_process *process, t_op_data *data)
{
	(void)vm;
	info("[%d]: live %d\n", process->pid, data->params[0]);
}

void op_ld(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	*output;

	(void)vm;
	if (!(output = get_register(process, data, 1)))
		return ;
	info("[%d]: ld %d r%d\n", process->pid, data->params[0], data->params[1]);
	*output = get_value(process, data, 0);
	process->carry = *output == 0;
}

void op_st(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*input_one;
	int32_t		*output;

	(void)vm;
	if (!(input_one = get_register(process, data, 0)) || (!(output = get_register(process, data, 1)) && !(output = get_indirect(process, data, 1))))
		return ;
	info("[%d]: st r%d %d\n", process->pid, data->params[0], data->params[1]);
	*output = *input_one;
}

void op_add(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*input_one;
	int32_t		*input_two;
	int32_t		*output;

	(void)vm;
	if (!(input_one = get_register(process, data, 0)) || !(input_two = get_register(process, data, 1)) || !(output = get_register(process, data, 2)))
		return ;
	info("[%d]: add r%d, r%d, r%d\n", process->pid, data->params[0], data->params[1], data->params[2]);
	*output = *input_one + *input_two;
	process->carry = *output == 0;
}

void op_sub(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*input_one;
	int32_t		*input_two;
	int32_t		*output;

	(void)vm;
	if (!(input_one = get_register(process, data, 0)) || !(input_two = get_register(process, data, 1)) || !(output = get_register(process, data, 2)))
		return ;
	info("[%d]: sub r%d, r%d, r%d\n", process->pid, data->params[0], data->params[1], data->params[2]);
	*output = *input_one - *input_two;
	process->carry = *output == 0;
}

void op_and(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*output;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	info("[%d]: and %d, %d, %d\n", process->pid, data->params[0], data->params[1], data->params[2]);
	*output = get_value(process, data, 0) & get_value(process, data, 1);
	process->carry = *output == 0;
}

void op_or(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*output;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	info("[%d]: or %d, %d, %d\n", process->pid, data->params[0], data->params[1], data->params[2]);
	*output = get_value(process, data, 0) | get_value(process, data, 1);
	process->carry = *output == 0;
}

void op_xor(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*output;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	info("[%d]: xor %d, %d, %d\n", process->pid, data->params[0], data->params[1], data->params[2]);
	*output = get_value(process, data, 0) ^ get_value(process, data, 1);
	process->carry = *output == 0;
}

void op_zjmp(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	target;

	(void)vm;
	info("[%d]: zjmp 0x%x\n", process->pid, data->params[0]);
	target = ((process->position + ((int16_t)data->params[0] % IDX_MOD) - 0x3 + MEM_SIZE) % MEM_SIZE);
	if (process->carry)
		process->position = target;
}

void op_ldi(t_vm *vm, t_process *process, t_op_data *data)
{
	(void)vm;
	(void)process;
	(void)data;
}

void op_sti(t_vm *vm, t_process *process, t_op_data *data)
{
	(void)vm;
	(void)process;
	(void)data;
}

void op_fork(t_vm *vm, t_process *process, t_op_data *data)
{
	info("[%d]: fork 0x%x\n", process->pid, data->params[0]);
	vm_fork(vm, process, (int16_t)data->params[0], 0);
}

void op_lld(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	*output;

	(void)vm;
	if (!(output = get_register(process, data, 1)))
		return ;
	info("[%d]: lld %d r%d\n", process->pid, data->params[0], data->params[1]);
	*output = get_value(process, data, 0);
	process->carry = *output == 0;
}

void op_lldi(t_vm *vm, t_process *process, t_op_data *data)
{
	(void)vm;
	(void)process;
	(void)data;
}

void op_lfork(t_vm *vm, t_process *process, t_op_data *data)
{
	info("[%d]: lfork 0x%x\n", process->pid, data->params[0]);
	vm_fork(vm, process, (int16_t)data->params[0], 1);
}

void op_aff(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	*input;

	(void)vm;
	info("[%d]: aff 0x%x\n", process->pid, data->params[0]);
	input = get_register(process, data, 0);
	ft_putchar((char)(*input % 256));
}
