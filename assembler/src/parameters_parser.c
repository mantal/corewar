#include "assembler.h"

static char		*get_next_param_position(t_env *env, char *data, int *spaces, int i)
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

static int		is_number(char *str, int n)
{
	int		i;

	i = 0;
	while (str[i] && i < n)
	{
		if (!(i == 0 && str[i] == '-'))
		{
			if (!ft_isdigit(str[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

static int		is_direct(char *line, int size, char *type)
{
	int		i;

	if (*line == DIRECT_CHAR && *(line + 1))
	{
		*type |= T_DIR;
		if (is_number(line + 1, size - 1))
			return (1);
		if (*(line + 1) != LABEL_CHAR || !*(line + 2))
			return (0);
		i = 2;
		while (line[i] && (i < size))
		{
			if (!ft_strchr(LABEL_CHARS, line[i]))
				return (0);
			i++;
		}
		if (i - 1 > LABEL_LENGTH)
			return (0);
		*type |= T_LAB;
		return (1);
	}
	return (0);
}

static int		is_indirect(char *line, int size, char *type)
{
	int		i;

	if (is_number(line, size - 1))
	{
		*type |= T_IND;
		return (1);
	}
	if (*(line) != LABEL_CHAR || !*(line + 1))
		return (0);
	i = 1;
	while (line[i] && (i < size))
	{
		if (!ft_strchr(LABEL_CHARS, line[i]))
			return (0);
		i++;
	}
	if (i - 1 > LABEL_LENGTH)
		return (0);
	*type = (T_LAB | T_IND);
	return (1);
}

static int		is_register(char *line, int size, char *type)
{
	int		no;

	if (*line == 'r')
	{
		if (!is_number(line + 1, size - 1))
			return (0);
		no = ft_atoi(line + 1);
		if (no >= 1 && no <= REG_NUMBER)
		{
			*type = T_REG;
			return (1);
		}
	}
	return (0);
}

int				parse_parameter(t_env *env, char *line, char *next,
	int no_param)
{
	int		size;
	t_param	*param;

	size = (int)(next - line);
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

	i = -1;
	while ((spaces = 0) || ++i < g_op_tab[env->current_instruction.index].nb_params)
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