/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:25:00 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:28:48 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int		get_label_offset(t_inst *instr, t_list *labels,
		char *label_name, int i)
{
	t_list	*tmp;

	tmp = labels;
	while (tmp)
	{
		if (!ft_strcmp(label_name, ((t_label*)tmp->content)->name))
		{
			instr->params[i].integer_value = ((t_label*)tmp->content)->offset -
				instr->offset;
			return (0);
		}
		tmp = tmp->next;
	}
	return (-1);
}

static int		value_fits_within_param_size(t_inst *instr, int i)
{
	long	mask;

	if (instr->params[i].integer_value >= 0)
	{
		mask = ((long)(~(0)) << ((instr->params[i].required_bytes << 3)));
		return (!(instr->params[i].integer_value & mask));
	}
	mask = ((long)(~(0)) << ((instr->params[i].required_bytes << 3) - 1));
	return (!(~(instr->params[i].integer_value) & mask));
}

static int		get_integer_value(t_inst *inst, t_list *labels, int i)
{
	int		o;

	o = (((inst->params[i].type & (T_REG | T_DIR))) ? 1 : 0);
	if (!(inst->params[i].type & T_LAB))
		inst->params[i].integer_value = ft_atoli(inst->params[i].value + o);
	else
	{
		if (get_label_offset(inst, labels, \
			inst->params[i].value + o + 1, i) < 0)
			return (error_label_not_found(inst, o, i));
	}
	if (!value_fits_within_param_size(inst, i))
		return (error_wrong_param_number_impl(inst, i));
	return (0);
}

static int		check_parameter(t_inst *instr, t_list *labels)
{
	int		i;

	i = 0;
	while (i < g_op_tab[instr->index].nb_params)
	{
		if (!(instr->params[i].type & g_op_tab[instr->index].param_types[i]))
			return (error_wrong_param_type(instr, i));
		if (get_integer_value(instr, labels, i))
			return (1);
		i++;
	}
	return (0);
}

int				check_instructions(t_list *list, t_list *labels)
{
	int		error;
	int		is_valid;
	t_list	*tmp;

	tmp = list;
	error = 0;
	if (!tmp)
		return (ft_error_retint("error: no instruction found\n", 1));
	while (tmp)
	{
		is_valid = check_parameter(tmp->content, labels);
		if (!error)
			error = is_valid;
		tmp = tmp->next;
	}
	return (error);
}
