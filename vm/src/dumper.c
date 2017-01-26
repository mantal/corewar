/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:00:22 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/26 12:05:31 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include "vm.h"

void		vm_dump(t_vm *vm)
{
	int i;

	i = 0;
	verbose("\n0x%x   : ", i);
	while (i < MEM_SIZE)
	{
		verbose("%s%x ", vm->memory[i] > 15 ? "" : "0", vm->memory[i]);
		if (!((i + 1) % 64) && i + 1 < MEM_SIZE)
		{
			if (i < 256)
				verbose("\n0x%x  : ", i);
			else
				verbose("\n0x%x : ", i);
		}
		i++;
	}
}
