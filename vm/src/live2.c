/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 18:37:13 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/26 18:08:16 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>
#include <stdlib.h>

bool		has_lived(t_vm *vm, int id)
{
	size_t i;

	i = 0;
	while (i < vm->last_live.size)
	{
		if (((t_program*)array_get(&vm->last_live, i))->id == id)
			return (true);
		i++;
	}
	return (false);
}

void		live(t_program *prg, t_vm *vm, int startup)
{
	if (!startup)
		info("un processus dit que le joueur %d(%s) est en vie\n", prg->id,
			prg->header.name);
	if (!prg->alive)
		array_add(&vm->last_live, prg);
	prg->alive = true;
	vm->lives++;
}

static void	print_death(t_vm *vm)
{
	long i;

	i = 0;
	if (vm->last_live.size < vm->programs.size)
	{
		while (i < (long)vm->programs.size)
		{
			if (!has_lived(vm, ((t_program*)array_get(&vm->programs,
				i))->id))
			{
				ft_printf("- : %s", ((t_program*)array_get(&vm->programs,
					i))->color);
				ft_printf("%d(%s)\x1B[0m\n",
					((t_program*)array_get(&vm->programs, i))->id,
				((t_program*)array_get(&vm->programs, i))->header.name);
			}
			i++;
		}
	}
}

void		print_alive(t_vm *vm)
{
	long	i;
	int		alive;

	alive = count_alive(vm);
	ft_printf(!alive ? "\n\nNo players alive!\n" : "\n\n%d players alive!\n",
		alive);
	if ((i = vm->last_live.size) > 0)
	{
		ft_printf("le joueur%s ", ((t_program*)array_get(&vm->last_live, i -
			1))->color);
		ft_printf("%d(%s)\x1B[0m a gagne\nLeaderboard: \n",
			((t_program*)array_get(&vm->last_live, i - 1))->id,
				((t_program*)array_get(&vm->last_live, i - 1))->header.name);
		while (i > 0)
		{
			ft_printf("%d : %s", vm->last_live.size - i + 1,
				((t_program*)array_get(&vm->last_live, i - 1))->color);
			ft_printf("%d(%s)\x1B[0m\n",
				((t_program*)array_get(&vm->last_live, i - 1))->id,
					((t_program*)array_get(&vm->last_live, i -
						1))->header.name);
			i--;
		}
		print_death(vm);
	}
}
