/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 18:37:13 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/25 18:37:32 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>
#include <stdlib.h>

void		live(t_program *prg, t_vm *vm)
{
	ft_printf("un processus dit que le joueur %d(%s) est en vie\n", prg->id,
		prg->header.name);
	if (!prg->alive)
		array_add(&vm->last_live, prg);
	prg->alive = true;
	vm->lives++;
}
