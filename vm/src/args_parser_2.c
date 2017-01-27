/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:29:11 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/27 12:00:57 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include "fterror.h"
#include "number_utils.h"
#include <ftio.h>

static bool	is_id_used(t_array *programs, int id)
{
	t_program *prog;

	while ((prog = array_next(programs)))
	{
		if (prog->id == id)
		{
			programs->it = 0;
			return (true);
		}
	}
	return (false);
}

void		args_n(const char **args, void *data)
{
	t_program	*prog;
	t_vm		*vm;

	vm = (t_vm *)data;
	prog = load_program(args[2], ft_atoi(args[1]));
	array_add(&vm->programs, prog);
}

bool		args_n_validate(const char **args, void *data)
{
	t_vm	*vm;
	int		id;

	vm = data;
	if (vm->programs.size >= 4)
	{
		error("Too many champions (4 max)\n");
		return (false);
	}
	if (!is_valid_number(args[1]))
	{
		error("Invalid champion id %s\n", args[1]);
		return (false);
	}
	id = ft_atoi(args[1]);
	if (is_id_used(&vm->programs, id))
	{
		error("Duplicate champion id %d\n", id);
		return (false);
	}
	return (true);
}
