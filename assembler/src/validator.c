#include "assembler.h"

void             check_header(t_env *env)
{
	if (!(*env->header.prog_name))
		ft_printf("Warning: program name not defined!\n");
	if (!(*env->header.comment))
		ft_printf("Warning: program comment not defined!\n");
	if ((env->header.prog_size = env->current_offset) > CHAMP_MAX_SIZE)
		ft_printf("Warning: program is %i too long\n", CHAMP_MAX_SIZE - env->header.prog_size);
}

int             is_data_correct(t_env *env)
{
    int error;

    error = 0;
    check_header(env);
    if (!check_instructions(env->instructions, env->labels))
        error = 1;
    return (error);
}