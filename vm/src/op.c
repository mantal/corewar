/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/01/25 14:59:13 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "op_utils.h"
#include <ftio.h>

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, &op_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &op_ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &op_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &op_add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &op_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, &op_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, &op_or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, &op_xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &op_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, &op_ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, &op_sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, &op_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &op_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, &op_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &op_lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, &op_aff}
};

void	op_live(t_vm *vm, t_process *process, t_op_data *data)
{
	int			id;
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
		live(prgm, vm, 0);
}

void	op_ld(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t	*output;

	(void)vm;
	if (!(output = get_register(process, data, 1)))
		return ;
	info("[%d]: ld %d r%d\n", process->pid, data->params[0], data->params[1]);
	*output = get_value(process, data, 0);
	process->carry = *output == 0;
}

void	op_st(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*input_one;
	int8_t		indirect_write;
	int32_t		*output;

	(void)vm;
	output = NULL;
	indirect_write = 0;
	if (!(input_one = get_register(process, data, 0))
					|| !(output = get_register(process, data, 1)))
	{
		if (input_one && is_indirect(process, data, 1))
			indirect_write = 1;
		else
			return ;
	}
	info("[%d]: st r%d %d\n", process->pid, data->params[0], data->params[1]);
	if (indirect_write)
		vm_memwrite(process, input_one, process->op_code_pos +
						((int16_t)data->params[1] % IDX_MOD),
						sizeof(*input_one));
	else
		*output = *input_one;
}

void	op_add(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*input_one;
	int32_t		*input_two;
	int32_t		*output;

	(void)vm;
	if (!(input_one = get_register(process, data, 0))
					|| !(input_two = get_register(process, data, 1))
					|| !(output = get_register(process, data, 2)))
		return ;
	info("[%d]: add r%d, r%d, r%d\n", process->pid, data->params[0],
					data->params[1], data->params[2]);
	*output = *input_one + *input_two;
	process->carry = *output == 0;
}

void	op_sub(t_vm *vm, t_process *process, t_op_data *data)
{
	int32_t		*input_one;
	int32_t		*input_two;
	int32_t		*output;

	(void)vm;
	if (!(input_one = get_register(process, data, 0))
					|| !(input_two = get_register(process, data, 1))
					|| !(output = get_register(process, data, 2)))
		return ;
	info("[%d]: sub r%d, r%d, r%d\n", process->pid, data->params[0],
					data->params[1], data->params[2]);
	*output = *input_one - *input_two;
	process->carry = *output == 0;
}
