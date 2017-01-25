/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:59:49 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 15:00:59 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_utils.h"
#include <ftio.h>

void	op_and(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*output;
	int32_t		input_one;
	int32_t		input_two;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	input_one = get_value(process, data, 0);
	input_two = get_value(process, data, 1);
	info("[%d]: and %d, %d, r%d\n", process->pid, input_one,
					input_two, data->params[2]);
	*output = input_one & input_two;
	process->carry = *output == 0;
}

void	op_or(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*output;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	info("[%d]: or %d, %d, %d\n", process->pid, data->params[0],
					data->params[1], data->params[2]);
	*output = get_value(process, data, 0) | get_value(process, data, 1);
	process->carry = *output == 0;
}

void	op_xor(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*output;

	(void)vm;
	if (!(output = get_register(process, data, 2)))
		return ;
	info("[%d]: xor %d, %d, %d\n", process->pid, data->params[0],
					data->params[1], data->params[2]);
	*output = get_value(process, data, 0) ^ get_value(process, data, 1);
	process->carry = *output == 0;
}

void	op_zjmp(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	target;

	(void)vm;
	info("[%d]: zjmp 0x%x\n", process->pid, data->params[0]);
	target = ((process->op_code_pos + ((int16_t)data->params[0] % IDX_MOD)
							+ MEM_SIZE) % MEM_SIZE);
	if (process->carry)
		process->position = target;
}
