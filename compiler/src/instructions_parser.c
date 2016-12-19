/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:25:49 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:39:29 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int		compute_offset_of_instruction(t_env *env)
{
	int		required_bytes;
	int		i;

	i = 0;
	required_bytes = 1;
	if (g_op_tab[env->current_instruction.index].has_pcode)
		required_bytes++;
	while (i < g_op_tab[env->current_instruction.index].nb_params)
	{
		required_bytes += env->current_instruction.params[i].required_bytes;
		i++;
	}
	return (required_bytes);
}

static int		get_index_of_instruction_in_opcode(char *data)
{
	int		i;
	int		len;

	i = 0;
	while (g_op_tab[i].name)
	{
		len = ft_strlen(g_op_tab[i].name);
		if (!ft_strncmp(data, g_op_tab[i].name, len) &&
				is_whitespace(data[len]))
			return (i);
		i++;
	}
	return (-1);
}

static int		parse_label(t_env *env, char *data)
{
	t_label	label;
	char	*label_end;
	char	*tmp;

	if ((label_end = ft_strchr(data, LABEL_CHAR)) == NULL)
		return (1);
	if ((label_end - data) > LABEL_LENGTH)
		return (1);
	tmp = data;
	while (tmp < label_end)
	{
		if (!ft_strchr(LABEL_CHARS, *tmp))
			return (1);
		tmp++;
	}
	ft_bzero(label.name, LABEL_LENGTH);
	ft_strncpy(label.name, data, label_end - data);
	label.offset = env->current_offset;
	list_add(&(env->labels), &label, sizeof(t_label));
	return (label_end - data + 1);
}

int				parse_instructions(t_env *env, char *data)
{
	int		label_offset;

	label_offset = 0;
	if ((env->current_instruction.index =
				get_index_of_instruction_in_opcode(data)) < 0)
	{
		if ((label_offset = parse_label(env, data)) < 0)
			return (error_label_expected(env, data));
		data += label_offset;
		if (is_end_of_line(data))
			return (0);
		data += count_whitespace_offset(data);
		if ((env->current_instruction.index =
					get_index_of_instruction_in_opcode(data)) < 0)
			return (error_label_expected(env, data));
	}
	if (parse_parameters(env, data +
				ft_strlen(g_op_tab[env->current_instruction.index].name)) < 0)
		return (1);
	env->current_instruction.offset = env->current_offset;
	env->current_instruction.line_number = env->line_number;
	list_add(&(env->instructions), &(env->current_instruction), sizeof(t_inst));
	env->current_offset += compute_offset_of_instruction(env);
	return (0);
}
