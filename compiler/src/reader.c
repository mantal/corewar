/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:26:32 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:47:21 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int	read_lines(int fd, t_env *env)
{
	int		ret;
	int		error;

	error = 0;
	while ((ret = ft_get_next(fd, &env->line, '\n')) > 0)
	{
		if (parse_line(env))
			error = 1;
		env->line_number++;
		free(env->line);
	}
	free(env->line);
	return (ret == -1 || error);
}

int			parse_file(t_env *env, char *fname)
{
	int		fd;
	int		error;

	error = 0;
	fd = open(fname, O_RDONLY);
	if (fd > 0)
	{
		error = read_lines(fd, env);
		close(fd);
	}
	else
	{
		error = 1;
		perror("asm");
	}
	return (!error);
}
