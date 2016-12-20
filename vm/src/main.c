/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:56:52 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/20 15:55:20 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"

int main(int argc, char **argv)
{
	t_vm		*vm;
	t_program	*p1 = NULL;

	p1 = load_program(argc > 1 ? argv[1] : "./test.cor");
	vm = vm_new();
	vm_new_process(vm, p1, 0, vm->memory);
	vm_exec(vm, array_get(&vm->process, 0), 0);
	return (0);
}
