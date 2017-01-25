/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:46:27 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 14:49:12 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include <ftio.h>
#include <stdint.h>
#include <stddef.h>

int32_t	swap_int32(int32_t val)
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
	return ((ptype == T_REG || ((ptype & T_REG) && pcode == REG_CODE))
					&& param > 0 && param <= REG_NUMBER);
}

int		is_indirect(t_process *process, t_op_data *data, int index)
{
	int32_t		ptype;
	int32_t		pcode;

	ptype = process->current_instruction->param_types[index];
	pcode = data->param_pcodes[index];
	return (ptype == T_IND || ((ptype & T_IND) && pcode == IND_CODE));
}
