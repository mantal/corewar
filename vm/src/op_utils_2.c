/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:53:05 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 14:53:27 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_utils.h"

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
		vm_memread(process, &tmp_ind, process->op_code_pos + tmp_ind,
						sizeof(tmp_ind));
		return (swap_int32(tmp_ind));
	}
	return (data->params[index]);
}
