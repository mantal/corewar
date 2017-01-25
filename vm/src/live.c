/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:15:12 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/25 16:07:33 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>
#include <stdlib.h>

void live(t_program *prg, t_vm *vm)
{
	ft_printf("un processus dit que le joueur %d(%s) est en vie\n", prg->id,
		prg->header.name);
	if (!prg->alive)
	{
		array_add(&vm->last_live, prg);
	}
	prg->alive = true;
	vm->lives++;
}

static int count_alive(t_vm *vm)
{
	size_t i;
	int rtn;

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

static void print_alive(t_vm *vm)
{
	size_t i;
	int alive;

	i = vm->last_live.size;
	alive = count_alive(vm);
	ft_printf(!alive ? "No players alive!\n" : "%d players alive!\n", alive);
	ft_printf("le joueur %d(%s) a gagne\n",
		((t_program*)array_get(&vm->programs, i - 1))->id,
			((t_program*)array_get(&vm->programs, i - 1))->header.name);
	ft_printf("Leaderboard: \n");
	while (i > 0)
	{
		ft_printf("%d : %d(%s)\n", vm->last_live.size - i + 1, 
			((t_program*)array_get(&vm->programs, i - 1))->id,
				((t_program*)array_get(&vm->programs, i - 1))->header.name);
		i--;
	}
}

static void stop(t_vm *vm)
{
	vm_dump(vm);
	print_alive(vm);
	ft_printf("Game over\n");
	exit(0);
}

void tick_cycles(t_vm *vm)
{
	long i;

	i = vm->process.size;
	while (--i >= 0)
		vm_exec(vm, array_get(&vm->process, i));
	if (vm->current_cycle == vm->next_die)
	{
		info("%d = %d\n", vm->current_cycle, vm->next_die);
		i = 0;
		while (i < vm->process.size)
		{
			if (!((t_process*)array_get(&vm->process, i))->owner->alive)
			{
				ft_printf("Le processus %d a été tué",
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
		array_clear(&vm->last_live);
	}
	vm->current_cycle++;
	if (vm->current_cycle >= vm->max_cycles)
		stop(vm);
}
