/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:56:52 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/26 18:26:25 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>

int	main(int argc, const char **argv)
{
	t_vm		*vm;
	t_program	*prog;
	int			i;
	int			spacing;

	vm = vm_new();
	parse_args(argc, argv, vm);
	i = vm->programs.size - 1;
	assign_colors(vm);
	while (i >= 0)
	{
		spacing = ((MEM_SIZE / vm->programs.size) * i) % MEM_SIZE;
		prog = array_get(&vm->programs, i);
		live(prog, vm, 1);
		vm_new_process(vm, prog, vm->memory, spacing);
		ft_memcpy(vm->memory + spacing, prog->program, prog->header.size);
		default_color(i, vm, spacing, prog->header.size);
		i--;
	}
	while (true)
		tick_cycles(vm);
}
