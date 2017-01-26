/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:29:11 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 17:29:36 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include "fterror.h"
#include "number_utils.h"

void	args_n(const char **args, void *data)
{
	t_program	*prog;
	t_vm		*vm;

	vm = (t_vm *)data;
	if (vm->programs.size >= 4)
		ft_error_msg("Too many champions\n");
	prog = load_program(args[2], ft_atoi(args[1]));
	array_add(&vm->programs, prog);
}

bool	args_n_validate(const char **args, void *data)
{
	(void)data;
	return (is_valid_number(args[1]));
}
