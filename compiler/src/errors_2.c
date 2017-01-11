/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:59:58 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 11:00:13 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int				error_wrong_param_number_impl(t_inst *instruction,
		int line_number)
{
	ft_printf("line %d: error: invalid parameter number for instruction %s\n",
			line_number, g_op_tab[instruction->index].name);
	return (-1);
}

char			*error_wrong_param_number(t_env *env)
{
	error_wrong_param_number_impl(&env->current_instruction, env->line_number);
	return (NULL);
}

char			error_invalid_parameter_format(t_env *env, char *end, int i)
{
	ft_printf("line %d, colum %d: error: parameter %d ", env->line_number,
			end - env->line, i);
	ft_printf("for instruction %s has an invalid format!\n",
			g_op_tab[env->current_instruction.index].name);
	return (-1);
}

int				error_wrong_param_type(t_inst *inst, int index)
{
	ft_printf("error: instruction cannot have a %s\n",
			g_op_tab[inst->index].name, get_param_type(inst, index));
	return (1);
}

int				error_label_not_found(t_inst *inst, int offset, int index)
{
	ft_printf("line %d error: failed to deference label name \"%s\" ",
			inst->line_number, inst->params[index].value + offset + 1);
	ft_printf("at parameter index %d for instruction %s\n",
			index, g_op_tab[inst->index].name);
	return (1);
}
