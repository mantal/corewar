/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:26:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/19 10:49:29 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static char		*get_output_name(char *path)
{
	char	*new;
	int		size;
	char	*tmp;

	size = ft_strlen(path);
	new = ft_malloc(size + 4);
	if (!new)
		return (NULL);
	ft_bzero(new, size + 4);
	ft_memcpy(new, path, size);
	if (!(tmp = ft_strrchr(new, '/')))
		tmp = new;
	if ((tmp = ft_strrchr(tmp, '.')))
		*tmp = '\0';
	ft_strcat(new, ".cor");
	return (new);
}

static void		write_header(t_env *env, int fd)
{
	unsigned int	real_size;

	real_size = env->header.size;
	env->header.magic = swap_uint(env->header.magic);
	env->header.size = swap_uint(env->header.size);
	write(fd, &env->header, sizeof(t_header));
	env->header.size = real_size;
}

static int		write_instructions(t_env *env, int fd)
{
	char	*data;
	t_list	*inst;
	int		i;

	if (!(data = (char*)ft_memalloc(sizeof(char) * (env->header.size + 3))))
		return (0);
	i = 0;
	inst = env->instructions;
	while (inst)
	{
		encode_inst((t_inst*)inst->content, data, &i);
		inst = inst->next;
	}
	write(fd, data, env->header.size);
	ft_memdel((void**)&data);
	return (1);
}

int				write_output(t_env *env, char *fname)
{
	char	*output;
	int		fd;

	if (!(output = get_output_name(fname)))
	{
		ft_printf("Allocation error during write_output!\n");
		return (0);
	}
	if ((fd = open(output, O_CREAT | O_WRONLY, 0644)) < 0)
	{
		perror("asm");
		ft_memdel((void**)&output);
		return (0);
	}
	ft_memdel((void**)&output);
	write_header(env, fd);
	if (!write_instructions(env, fd))
	{
		ft_printf("Allocation error during write_output!\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (1);
}
