/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:26:41 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:48:21 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void			check_header(t_env *env)
{
	if (!(*env->header.name))
		ft_printf("Warning: program name not defined!\n");
	if (!(*env->header.description))
		ft_printf("Warning: program description not defined or empty!\n");
	if ((env->header.size = env->current_offset) > CHAMP_MAX_SIZE)
		ft_printf("Warning: program is %d bytes too long\n",
				env->header.size - CHAMP_MAX_SIZE);
}

int				is_data_correct(t_env *env)
{
	int error;

	error = 0;
	check_header(env);
	if (!check_instructions(env->instructions, env->labels))
		error = 1;
	return (error);
}
