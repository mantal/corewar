/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:15:12 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/17 17:25:47 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>
#include <stdlib.h>

void live(t_program *prg, t_vm *vm)
{
    ft_printf("un processus dit que le joueur %s(%s) est en vie", prg->id,
        prg->header.name);
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

    i = 0;
    alive = count_alive(vm);
    if (alive == 0)
    {
        ft_printf("No players alive!\n");
        return ;
    }
    while (i < vm->programs.size)
    {
        if (((t_program*)array_get(&vm->programs, i))->alive)
        {
            if (alive == 1)
            {
                ft_printf("%s(%s) is the winner!\n", ((t_program*)array_get(&vm->programs,
                    i))->id, ((t_program*)array_get(&vm->programs, i))->header.name);
                break ;
            }
            ft_printf("%s(%s) is still alive!\n", ((t_program*)array_get(&vm->programs,
                i))->id, ((t_program*)array_get(&vm->programs, i))->header.name);
        }
        i++;
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
    if (false && vm->current_cycle == vm->next_die)
    {
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
        if (vm->lives >= NBR_LIVE)
            vm->cycles_to_die -= CYCLE_DELTA;
        vm->lives = 0;
        vm->next_die = vm->current_cycle + vm->cycles_to_die;
        if (count_alive(vm) <= 1)
            stop(vm);
    }
    vm->current_cycle++;
    if (vm->current_cycle >= vm->max_cycles)
        stop(vm);
}
