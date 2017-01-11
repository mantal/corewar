/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:25:56 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:40:42 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_env	*init_data(t_env *env)
{
	env->line_number = 1;
	env->header.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(env->header.name, PROG_NAME_LENGTH);
	ft_bzero(env->header.description, COMMENT_LENGTH);
	env->header.size = 0;
	return (env);
}

void	destroy_entry(void *ptr, size_t size)
{
	(void)size;
	ft_memdel(&ptr);
}

void	destroy_data(t_env *env)
{
	if (env->instructions)
		ft_lstdel(&env->instructions, destroy_entry);
	if (env->labels)
		ft_lstdel(&env->labels, destroy_entry);
}

int		main(int ac, char **av)
{
	t_env	env;

	if (ac >= 2)
	{
		init_data(&env);
		if (&env && parse_file(&env, *(av + 1)) && is_data_correct(&env))
		{
			ft_printf("compillation done!\nname: %s\ndesc: %s\nsize: %d\n",
					env.header.name, env.header.description, env.header.size);
			write_output(&env, *(av + 1));
		}
		destroy_data(&env);
	}
	else
		ft_printf("Usage: %s source.s\n", *av);
	return (0);
}
