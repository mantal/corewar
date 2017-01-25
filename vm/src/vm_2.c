/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:16:45 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 18:25:22 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ftio.h>

void		vm_decode_params(t_process *process, t_op *op, t_op_data *param)
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
	uint8_t		op_code;
	t_op		*op;
	t_op_data	param;
	t_process	*process = ((t_process*)array_get(&vm->process, index));

	process->op_code_pos = process->position;
	debug("[%u] >>  Reading opcode (PC: 0x%X)\n", process->pid, process->entry_point + process->op_code_pos);
	vm_read(process, &op_code, sizeof(op_code));
	if (op_code == 0 || op_code > 16)//TODO DONT HARD CODE
	{
		warning("Process %u created by %s tried to execute an illegal instruction %d\n",
						process->pid, process->owner->header.name, op_code);
		process->freeze = 1;
		return ;
	}
	op = &g_op_tab[op_code - 1];
	process->current_instruction = op;
	debug("[%u] Instruction %s\n", process->pid, op->name);
	vm_decode_params(process, op, &param);
	if (check_param(process->current_instruction, &param))
		op->handler(vm, process, &param);
	else
		warning("[%u] Invalid arguments!\nInstruction skipped!\n");
	((t_process*)array_get(&vm->process, index))->freeze += op->nb_cycles;
}

void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t *pc,
	uint32_t start)
{
	t_process	process;

	process.carry = false;
	process.owner = prog;
	ft_bzero(process.reg, sizeof(uint32_t) * REG_NUMBER);
	process.reg[0] = prog->id;
	process.entry_point = pc;
	process.position = start;
	process.pid = vm->process.size;
	process.freeze = 0;
	array_add(&vm->process, &process);
}

void		vm_fork(t_vm *vm, t_process *process, int16_t pc, int long_mode)
{
	t_process	fork;
	uint32_t	position;
	int			i;

	i = -1;
	if (long_mode)
		position = ((process->op_code_pos + pc + MEM_SIZE) % MEM_SIZE);
	else
		position = ((process->op_code_pos + (pc % IDX_MOD) + MEM_SIZE)
						% MEM_SIZE);
	fork.carry = process->carry;
	fork.owner = process->owner;
	ft_bzero(fork.reg, sizeof(uint32_t) * REG_NUMBER);
	while (++i < REG_NUMBER)
		fork.reg[i] = process->reg[i];
	fork.entry_point = process->entry_point;
	fork.position = position;
	fork.pid = vm->process.size;
	fork.freeze = 0;
	array_add(&vm->process, &fork);
}

t_vm		*vm_new(void)
{
	t_vm	*vm;

	vm = ft_malloc(sizeof(t_vm));
	vm->lives = 0;
	vm->current_cycle = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->next_die = vm->cycles_to_die;
	ft_bzero(vm->memory, sizeof(vm->memory));
	info("Virtual memory start at position 0x%X\n", vm->memory);
	array_init(&vm->programs, sizeof(t_program), 0);
	array_init(&vm->process, sizeof(t_process), 0);
	return (vm);
}
