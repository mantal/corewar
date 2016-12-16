#include "assembler.h"

int     error_space_expected(t_env *env, char *line)
{
    ft_printf("line %i, colum %i: error: space expected before quotes\n",
        env->line_number, line - env->line);
    return (1);
}

int     error_opening_quote_expected(t_env *env)
{
    ft_printf("line %i: error: opening quote expected\n", env->line_number);
    return (1);
}

int     error_closing_quote_expected(t_env *env)
{
    ft_printf("line %i: error: closing quote expected\n", env->line_number);
    return (1);
}

int     error_string_too_long(t_env *env, int max_length)
{
    ft_printf("line %i: error: string is too long! (Max: %i)\n", env->line_number, max_length);
    return (1);
}

int     error_unexpected_characters(t_env *env, char *end)
{
    ft_printf("line %i, colum %i: error: unexpected character found!\n",
        env->line_number, end - env->line);
    return (1);
}

int     error_duplicate_symbol(t_env *env, char *type)
{
    ft_printf("line %i: error: duplicate symbol \"%s\"\n", env->line_number, type);
    return (1);
}

int     error_label_expected(t_env *env, char *end)
{
    ft_printf("line %i, colum %i: error: instruction or label name expected!\n",
        env->line_number, end - env->line);
    return (1);
}

int     error_wrong_param_number_impl(t_inst *instruction, int line_number)
{
    ft_printf("line %i: error: invalid parameter number for instruction %s\n", line_number, g_op_tab[instruction->index].name);
    return (-1);
}

char    *error_wrong_param_number(t_env *env)
{
    error_wrong_param_number_impl(&env->current_instruction, env->line_number);
    return (NULL);
}

char			error_invalid_parameter_format(t_env *env, char *end, int i)
{
    ft_printf("line %i, colum %i: error: parameter %i for instruction %s has an invalid format!\n",
        env->line_number, end - env->line, i, g_op_tab[env->current_instruction.index].name);
    return (-1);
}

int             error_wrong_param_type(t_inst *inst, int index)
{
    ft_printf("error: instruction cannot have a %s\n", g_op_tab[inst->index].name, get_param_type(inst, index));
    return (1);
}

int             error_label_not_found(t_inst *inst, int offset, int index)
{
    ft_printf("line %i error: failed to deference label name \"%s\" at parameter index %i for instruction %s\n", inst->line_number, inst->params[index].value + offset + 1, index, g_op_tab[inst->index].name);
    return (1);
}
