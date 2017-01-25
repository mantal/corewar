/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:20:14 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 15:20:56 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_utils.h"
#include <ftio.h>

void	op_aff(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	*input;

	(void)vm;
	if ((input = get_register(process, data, 0)))
		info("[%d]: aff %c\n", process->pid, (char)(*input % 256));
}

void	op_ldi(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	input[2];
	int32_t	target_addr;
	int32_t	*output;

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
	info("[%d]: ldi %d, %d, r%d\n", process->pid, data->params[0],
					data->params[1], data->params[2]);
	vm_memread(process, output, process->op_code_pos
					+ (target_addr % IDX_MOD), sizeof(*output));
	*output = swap_int32(*output);
}
