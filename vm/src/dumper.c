/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:00:22 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/25 16:15:27 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include "vm.h"

void		vm_dump(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("\n0x%x   : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%c%x ", vm->memory[i] > 15 ? 0 : '0', vm->memory[i]);
		if (!((i + 1) % 64))
		{
			if (i < 256)
				ft_printf("\n0x%x  : ", i);
			else
				ft_printf("\n0x%x : ", i);
		}
		i++;
	}
}
