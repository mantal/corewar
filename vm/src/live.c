/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:15:12 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/12 18:00:58 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>

void live(t_program *prg, t_vm *vm)
{
    ft_printf("un processus dit que le joueur %s(%s) est en vie", prg->id,
        prg->header.name);
    prg->alive = true;
    vm->lives++;
}

void tick_cycles(t_vm *vm)
{
    int i;

    i = vm->process.size;
    while (--i >= 0)
        vm_exec(vm, array_get(vm->process, i));
    if (vm->current_cycle == vm->next_die)
    {
        i = 0;
        while (i < vm->process.size)
        {
            if (array_get(vm->process, i).owner->alive)
            {
                array_get(vm->process, i).owner->alive = false;
                vm->lives++;
            }
            else
            {
                ft_printf("Le processus %d a été tué",
                    array_get(vm->process, i).pid);
                array_remove(vm->process, i);
            }
            i++;
        }
        if (vm->lives >= NBR_LIVE)
            vm->cycles_to_die -= CYCLE_DELTA;
        vm->lives = 0;
        vm->next_die = vm->current_cycle + vm->cycles_to_die;
    }
    vm->current_cycle++;
    if (vm->current_cycle >= vm->max_cycles)
    {
        vm_dump(vm);
        ft_printf("Game over\n");
        exit(0);
    }
}
