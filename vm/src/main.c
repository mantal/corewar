/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:56:52 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/12 18:01:08 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"

int main(int argc, char **argv)
{
	t_vm		*vm;
	int i;

	vm = vm_new();
	array_init(&vm->programs, sizeof(t_program), 0);
	parse_args(argc - 1, argv + 1, vm);
	i = vm->programs.size - 1;
	while (i >= 0)
	{
		vm_new_process(vm, array_get(&vm->programs, i), vm->memory);
		i--;
	}
	vm_exec(vm, array_get(&vm->process, 0));
	return (0);
}
