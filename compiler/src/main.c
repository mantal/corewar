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

t_env	*init_data(void)
{
	t_env	*env;

	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		return (NULL);
	ft_bzero(env, sizeof(t_env));
	env->line_number = 1;
	env->header.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(env->header.name, PROG_NAME_LENGTH);
	ft_bzero(env->header.description, COMMENT_LENGTH);
	env->header.size = 0;
	return (env);
}

int		main(int ac, char **av)
{
	t_env	*env;

	if (ac >= 2)
	{
		env = init_data();
		if (env && parse_file(env, *(av + 1)) && is_data_correct(env))
		{
			ft_printf("compillation done!\nname: %s\ndesc: %s\nsize: %d\n",
				env->header.name, env->header.description, env->header.size);
			write_output(env, *(av + 1));
		}
	}
	else
		ft_printf("Usage: %s source.s\n", *av);
	return (0);
}
