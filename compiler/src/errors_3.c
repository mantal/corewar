/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 11:00:41 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 11:02:02 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int				error_duplicate_symbol(t_env *env, char *type)
{
	ft_printf("line %d: error: duplicate symbol \"%s\"\n",
			env->line_number, type);
	return (1);
}

int				error_label_expected(t_env *env, char *end)
{
	ft_printf("line %d, colum %d: error: instruction or label name expected!\n"
			, env->line_number, end - env->line);
	return (1);
}
