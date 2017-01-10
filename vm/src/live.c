/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:15:12 by bel-baz           #+#    #+#             */
/*   Updated: 2016/12/21 17:15:13 by bel-baz          ###   ########.fr       */
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
    if (!(vm->current_cycle % vm->cycles_to_die))
    {
        // check process live
        if (vm->lives >= NBR_LIVE)
            vm->cycles_to_die -= CYCLE_DELTA;
    }
    vm->current_cycle++;
    if (vm->current_cycle >= vm->max_cycles)
        // kill vm
}
