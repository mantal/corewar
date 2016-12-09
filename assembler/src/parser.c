#include "assembler.h"

static int		extract_quote_str(t_env *env, char **line, char **end,
	int max_length)
{
	if (!is_whitespace(**line))
		return (error_space_expected(env, *line));
	*line += count_whitespace_offset(*line);
	if (*(*line += count_whitespace_offset(*line)) != '"')
		return (error_opening_quote_expected(env));
	if ((*end = ft_strchr(*line + 1, '"')) == NULL)
		return (error_closing_quote_expected(env));
	if ((*end - 1) - (*line + 1) > max_length)
		return (error_string_too_long(env, max_length));
	return (0);
}

static int     parse_extra(t_env *env, char *data, char *type, char *prev_data)
{
	char	*end;

    data += ft_strlen(type);
	if (*prev_data)
		return (error_duplicate_symbol(env, type));
	if (extract_quote_str(env, &data, &end, PROG_NAME_LENGTH))
		return (1);
	ft_strncpy(prev_data, data + 1, (end - 1) - (data + 1) + 1);
	if (!is_end_of_line(end + 1))
		return (error_unexpected_characters(env, end + 1));
	return (0);
}

int            parse_line(t_env *env)
{
    if (!(*env->line) || is_comment_char(*env->line))
		return (0);
    if (!ft_strncmp(env->line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
        return (parse_extra(env, env->line, NAME_CMD_STRING, env->header.prog_name));
    else if (!ft_strncmp(env->line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
        return (parse_extra(env, env->line, COMMENT_CMD_STRING, env->header.comment));
    return (parse_instructions(env, env->line));
}