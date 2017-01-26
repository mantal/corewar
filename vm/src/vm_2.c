/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:16:45 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/26 17:53:27 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ftio.h>

void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t *pc,
	uint32_t start)
{
	t_process	process;

	process.carry = false;
	process.owner = (t_program *)prog;
	ft_bzero(process.reg, sizeof(uint32_t) * REG_NUMBER);
	process.reg[0] = prog->id;
	process.entry_point = pc;
	process.position = start;
	process.pid = vm->process.size;
	process.freeze = 0;
	process.current_instruction = NULL;
	process.vm = vm;
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
	fork.current_instruction = NULL;
	fork.vm = vm;
	array_add(&vm->process, &fork);
}

t_vm		*vm_new(void)
{
	t_vm	*vm;

	vm = ft_malloc(sizeof(t_vm));
	ft_bzero(vm, sizeof(t_vm));
	vm->lives = 0;
	vm->current_cycle = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->next_die = vm->cycles_to_die;
	ft_bzero(vm->memory, sizeof(vm->memory));
	ft_bzero(vm->memory_owner, sizeof(vm->memory_owner));
	debug("Virtual memory start at position 0x%X\n", vm->memory);
	array_init(&vm->programs, sizeof(t_program), 0);
	array_init(&vm->last_live, sizeof(t_program), 0);
	array_init(&vm->process, sizeof(t_process), 0);
	return (vm);
}
