/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:56:52 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/17 16:31:51 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftio.h>

int main(int argc, char **argv)
{
	t_vm		*vm;
	t_program	*prog;
	int i;
	int			spacing;

	g_ftio_verbose_level = FTIO_DEBUG;
	vm = vm_new();
	array_init(&vm->programs, sizeof(t_program), 0);
	parse_args(argc - 1, argv + 1, vm);
	i = vm->programs.size - 1;
	while (i >= 0)
	{
		spacing = ((MEM_SIZE / vm->programs.size) * i) % MEM_SIZE;
		prog = array_get(&vm->programs, i);
		vm_new_process(vm, prog, vm->memory + spacing, 0);
		ft_memcpy(vm->memory + spacing, prog->program, prog->header.size);
		i--;
	}

	while (true)
		tick_cycles(vm);
}
