#include "assembler.h"

bool	is_comment_char(char c)
{
	return COMMENT_CHAR == c;
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