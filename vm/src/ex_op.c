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

int32_t swap_int32(int32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return ((val << 16) | ((val >> 16) & 0xFFFF));
}

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

int		is_register(t_process *process, t_op_data *data, int index)
{
	int32_t		ptype;
	int32_t		param;
	int32_t		pcode;

	ptype = process->current_instruction->param_types[index];
	param = data->params[index];
	pcode = data->param_pcodes[index];
	return ((ptype == T_REG || ((ptype & T_REG) && pcode == REG_CODE)) && param > 0 && param <= REG_NUMBER);
}

int		is_indirect(t_process *process, t_op_data *data, int index)
{
	int32_t		ptype;
	int32_t		pcode;

	ptype = process->current_instruction->param_types[index];
	pcode = data->param_pcodes[index];
	return (ptype == T_IND || ((ptype & T_IND) && pcode == IND_CODE));
}

int32_t	*get_register(t_process *process, t_op_data *data, int index)
{
	int32_t		param;

	param = data->params[index];
	if (is_register(process, data, index))
		return ((int32_t *)(process->reg + param - 1));
	else
		return (NULL);
}

int32_t	get_value(t_process *process, t_op_data *data, int index)
{
	int32_t	*tmp;
	int32_t	tmp_ind;

	tmp_ind = data->params[index];
	if (process->current_instruction->opcode != 0xA
		&& process->current_instruction->opcode != 0xD
		&& process->current_instruction->opcode != 0xE)
		tmp_ind %= IDX_MOD;
	if ((tmp = get_register(process, data, index)))
		return (*tmp);
	else if (is_indirect(process, data, index))
	{
		vm_memread(process, &tmp_ind, process->op_code_pos + tmp_ind, sizeof(tmp_ind));
		return (swap_int32(tmp_ind));
	}
	return (data->params[index]);
}

void op_live(t_vm *vm, t_process *process, t_op_data *data)
{
	int	id;
	uint32_t	i;
	t_program	*prgm;

	prgm = NULL;
	i = 0;
	id = data->params[0];
	info("[%d]: live %d\n", process->pid, id);
	while (i < vm->programs.size)
	{
		prgm = array_get(&vm->programs, i);
		if (prgm->id == id)
			break ;
		else
			prgm = NULL;
		i++;
	}
	if (prgm)
		live(prgm, vm);
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
	int8_t		indirect_write;
	int32_t		*output;

	(void)vm;
	output = NULL;
	indirect_write = 0;
	if (!(input_one = get_register(process, data, 0)) || !(output = get_register(process, data, 1)))
	{
		if (input_one && is_indirect(process, data, 1))
			indirect_write = 1;
		else
			return ;
	}
	info("[%d]: st r%d %d\n", process->pid, data->params[0], data->params[1]);
	if (indirect_write)
		vm_memwrite(process, input_one, process->op_code_pos + data->params[1], sizeof(*input_one));
	else
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
	int32_t		input_one;
	int32_t		input_two;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	input_one = get_value(process, data, 0);
	input_two = get_value(process, data, 1);
	info("[%d]: and %d, %d, r%d\n", process->pid, input_one, input_two, data->params[2]);
	*output = input_one & input_two;
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
	target = ((process->op_code_pos + ((int16_t)data->params[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	if (process->carry)
		process->position = target;
}

void op_ldi(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		input[2];
	int32_t		target_addr;
	int32_t		*output;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	input[0] = get_value(process, data, 0);
	if (!is_register(process, data, 0))
		input[0] = (int16_t)input[0];
	target_addr = input[0];
	input[1] = get_value(process, data, 1);
	if (!is_register(process, data, 1))
		input[1] = (int16_t)input[1];
	target_addr += input[1];
	info("[%d]: ldi %d, %d, r%d\n", process->pid, data->params[0], data->params[1],  data->params[2]);
	vm_memread(process, output, process->op_code_pos + (target_addr % IDX_MOD), sizeof(*output)); // TODO: check if IDX_MOD needed here
	*output = swap_int32(*output);
}

void op_sti(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		input[2];
	int32_t		target_addr;
	int32_t		*input_reg;

	(void)vm;
	if (!(input_reg = get_register(process, data, 0)))
		return ;
	input[0] = get_value(process, data, 1);
	if (!is_register(process, data, 1))
		input[0] = (int16_t)input[0];
	target_addr = input[0];
	input[1] = get_value(process, data, 2);
	if (!is_register(process, data, 2))
		input[1] = (int16_t)input[1];
	target_addr += input[1];
	info("[%d]: sti r%d, %d, %d\n", process->pid, data->params[0], data->params[1],  data->params[2]);
	vm_memwrite(process, input_reg, process->op_code_pos + (target_addr % IDX_MOD), sizeof(*input_reg));
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
	int32_t		input[2];
	int32_t		target_addr;
	int32_t		*output;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	input[0] = get_value(process, data, 0);
	if (!is_register(process, data, 0))
		input[0] = (int16_t)input[0];
	target_addr = input[0];
	input[1] = get_value(process, data, 1);
	if (!is_register(process, data, 1))
		input[1] = (int16_t)input[1];
	target_addr += input[1];
	info("[%d]: lldi %d, %d, r%d\n", process->pid, data->params[0], data->params[1],  data->params[2]);
	vm_memread(process, output, process->op_code_pos + target_addr, sizeof(*output));
	*output = swap_int32(*output);
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
