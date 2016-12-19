/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_parser_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:52:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:55:09 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		is_number(char *str, int n)
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

int		is_direct(char *line, int size, char *type)
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

int		is_indirect(char *line, int size, char *type)
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

int		is_register(char *line, int size, char *type)
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
