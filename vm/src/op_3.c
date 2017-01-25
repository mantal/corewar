/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:01:28 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 15:02:48 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_utils.h"
#include <ftio.h>

void	op_sti(t_vm *vm, t_process *process, t_op_data *data)
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
	info("[%d]: sti r%d, %d, %d\n", process->pid, data->params[0],
					data->params[1], data->params[2]);
	vm_memwrite(process, input_reg, process->op_code_pos
					+ (target_addr % IDX_MOD), sizeof(*input_reg));
}

void	op_fork(t_vm *vm, t_process *process, t_op_data *data)
{
	info("[%d]: fork 0x%x\n", process->pid, data->params[0]);
	vm_fork(vm, process, (int16_t)data->params[0], 0);
}

void	op_lld(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	*output;

	(void)vm;
	if (!(output = get_register(process, data, 1)))
		return ;
	info("[%d]: lld %d r%d\n", process->pid, data->params[0], data->params[1]);
	*output = get_value(process, data, 0);
	process->carry = *output == 0;
}

void	op_lldi(t_vm *vm, t_process *process, t_op_data *data)
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
	info("[%d]: lldi %d, %d, r%d\n", process->pid, data->params[0],
					data->params[1], data->params[2]);
	vm_memread(process, output, process->op_code_pos + target_addr,
					sizeof(*output));
	*output = swap_int32(*output);
	process->carry = *output == 0;
}

void	op_lfork(t_vm *vm, t_process *process, t_op_data *data)
{
	info("[%d]: lfork 0x%x\n", process->pid, data->params[0]);
	vm_fork(vm, process, (int16_t)data->params[0], 1);
}
