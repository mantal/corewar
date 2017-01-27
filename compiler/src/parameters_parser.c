/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:26:19 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:54:42 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static char		*get_next_param_position(t_env *env, char *data, int *spaces,
		int i)
{
	char	*next;

	if (i != g_op_tab[env->current_instruction.index].nb_params - 1)
	{
		if ((next = ft_strchr(data, SEPARATOR_CHAR)) == NULL)
			return (error_wrong_param_number(env));
		while (is_whitespace(*(next - 1 - *spaces)))
			(*spaces)++;
	}
	else
	{
		next = data + count_word_offset(data);
		if (!is_end_of_line(next) && ft_strchr(data, SEPARATOR_CHAR) != NULL)
			return (error_wrong_param_number(env));
	}
	return (next);
}

char			parse_parameter(t_env *env, char *line, char *next,
		int no_param)
{
	int		size;
	t_param	*param;

	size = (int)(next - line);
	if (size <= 0)
		return (error_invalid_parameter_format(env, line, no_param));
	if (size > PARAM_LENGTH)
		return (-1);
	param = &env->current_instruction.params[no_param];
	param->type = 0;
	ft_bzero(param->value, PARAM_LENGTH);
	ft_strncpy(param->value, line, size);
	if (is_register(line, size, &param->type))
		return (1);
	if (is_direct(line, size, &param->type))
	{
		if (g_op_tab[env->current_instruction.index].has_idx)
			return (2);
		return (4);
	}
	if (is_indirect(line, size, &param->type))
		return (2);
	return (error_invalid_parameter_format(env, line, no_param));
}

int				parse_parameters(t_env *env, char *data)
{
	t_param	*param;
	int		spaces;
	char	*next;
	int		i;

	next = NULL;
	i = -1;
	while ((spaces = 0) ||
			++i < g_op_tab[env->current_instruction.index].nb_params)
	{
		data += count_whitespace_offset(data);
		if (!(next = get_next_param_position(env, data, &spaces, i)))
			return (1);
		param = &env->current_instruction.params[i];
		param->required_bytes = parse_parameter(env, data, next - spaces, i);
		if (param->required_bytes < 0)
			return (1);
		data = next + 1;
	}
	if (!is_end_of_line(next))
		return (error_unexpected_characters(env, next - 1));
	return (0);
}
