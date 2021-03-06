/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:15:12 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/26 18:05:45 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>
#include <stdlib.h>

int			count_alive(t_vm *vm)
{
	size_t	i;
	int		rtn;

	i = 0;
	rtn = 0;
	while (i < vm->programs.size)
	{
		if (((t_program*)array_get(&vm->programs, i))->alive)
			rtn++;
		i++;
	}
	return (rtn);
}

static void	stop(t_vm *vm)
{
	if (vm->dump)
		vm_dump(vm);
	print_alive(vm);
	ft_printf("Game over\n");
	exit(0);
}

static void	tick_cycles2(t_vm *vm)
{
	long i;

	i = 0;
	while (i < (long)vm->process.size)
	{
		if (!((t_process*)array_get(&vm->process, i))->owner->alive)
		{
			info("\x1B[35mLe processus %d a été tué\n\x1B[0m",
				((t_process*)array_get(&vm->process, i))->pid);
			array_remove(&vm->process, i);
		}
		i++;
	}
	if (vm->lives >= NBR_LIVE || vm->last_die_decr >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->last_die_decr = 0;
	}
	else
		vm->last_die_decr++;
	vm->lives = 0;
	vm->next_die = vm->current_cycle + vm->cycles_to_die;
	if (count_alive(vm) <= 1)
		stop(vm);
}

void		tick_cycles(t_vm *vm)
{
	long i;

	i = vm->process.size;
	debug("It's cycle %d\n", vm->current_cycle + 1);
	while (--i >= 0)
	{
		((t_process*)array_get(&vm->process, i))->freeze--;
		if (((t_process*)array_get(&vm->process, i))->freeze <= 0)
			vm_exec(vm, i);
	}
	if (vm->current_cycle == vm->next_die)
	{
		info("\x1B[31m\x1B[1mDIE %d = %d\n\x1B[0m\x1B[22m", vm->current_cycle,
			vm->next_die);
		tick_cycles2(vm);
		array_clear(&vm->last_live);
		i = -1;
		while (++i < (long)vm->process.size)
			((t_process*)array_get(&vm->process, i))->owner->alive = false;
	}
	vm->current_cycle++;
	if (vm->current_cycle >= vm->max_cycles)
		stop(vm);
}
