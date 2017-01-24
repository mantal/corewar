/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:26:01 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:41:26 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

bool	is_comment_char(char c)
{
	return (COMMENT_CHAR == c || COMMENT_CHAR_ASM == c);
}

bool	is_whitespace(char c)
{
	return ((c == ' ') || (c == '\t'));
}

int		count_whitespace_offset(char *str)
{
	int		i;

	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	return (i);
}

int		count_word_offset(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !is_whitespace(str[i]))
		i++;
	return (i);
}

bool	is_end_of_line(char *line)
{
	int		w_offset;
	char	end_char;

	w_offset = count_whitespace_offset(line);
	end_char = *(line + w_offset);
	return ((end_char == '\0') || (is_comment_char(end_char)));
}
