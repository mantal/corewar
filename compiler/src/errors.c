/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:25:37 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 11:00:29 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int				error_space_expected(t_env *env, char *line)
{
	ft_printf("line %d, colum %d: error: space expected before quotes\n",
			env->line_number, line - env->line);
	return (1);
}

int				error_opening_quote_expected(t_env *env)
{
	ft_printf("line %d: error: opening quote expected\n", env->line_number);
	return (1);
}

int				error_closing_quote_expected(t_env *env)
{
	ft_printf("line %d: error: closing quote expected\n", env->line_number);
	return (1);
}

int				error_string_too_long(t_env *env, int max_length)
{
	ft_printf("line %d: error: string is too long! (Max: %d)\n",
			env->line_number, max_length);
	return (1);
}

int				error_unexpected_characters(t_env *env, char *end)
{
	ft_printf("line %d, colum %d: error: unexpected character found!\n",
			env->line_number, end - env->line);
	return (1);
}
