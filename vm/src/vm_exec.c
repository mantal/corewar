/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 14:48:56 by tguillem          #+#    #+#             */
/*   Updated: 2017/01/26 14:48:56 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ftio.h>
#define IIS ("Process %u from %s tried to execute an illegal instruction %d\n")
#define IAS ("[%u] Invalid arguments!\nInstruction skipped!\n")

static void	vm_exec_freeze(t_process *process)
{
	uint8_t		op_code;
	t_op		*op;

	op = process->current_instruction;
	process->op_code_pos = process->position;
	debug("[%u] >>  Reading opcode (PC: 0x%X)\n", process->pid,
				process->entry_point + process->op_code_pos);
	vm_read(process, &op_code, sizeof(op_code));
	if (op_code == 0 || op_code > 16)
	{
		warning(IIS, process->pid, process->owner->header.name, op_code);
		process->freeze = 1;
		process->current_instruction = NULL;
		return ;
	}
	op = &g_op_tab[op_code - 1];
	process->current_instruction = op;
	debug("[%u] Instruction %s, freezing %d cycles\n", process->pid,
		op->name, op->nb_cycles);
	process->freeze = op->nb_cycles - 1;
}

static void	vm_decode_params(t_process *process, t_op *op, t_op_data *param)
{
	uint8_t	pcode;
	int		i;

	pcode = 0;
	if (op->has_pcode)
	{
		debug("[%u]>>  Reading pcode\n", process->pid);
		vm_read(process, &pcode, sizeof(pcode));
		get_param_pcode(pcode, param->param_pcodes);
	}
	else
		get_param_pcode(0x80, param->param_pcodes);
	i = 0;
	while (i < op->nb_params)
	{
		param->params[i] = vm_get_param(process, op, param->param_pcodes[i]);
		i++;
	}
}

void		vm_exec(t_vm *vm, size_t index)
{
	t_op		*op;
	t_op_data	param;
	t_process	*process;

	process = ((t_process*)array_get(&vm->process, index));
	if (process->current_instruction)
	{
		op = process->current_instruction;
		vm_decode_params(process, op, &param);
		if (check_param(op, &param))
			op->handler(vm, process, &param);
		else
			warning(IAS, process->pid);
		process->current_instruction = NULL;
	}
	else
		vm_exec_freeze(process);
}
