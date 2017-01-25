/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:36:38 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/16 15:51:04 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "program.h"
#include <ftendianess.h>
#include <ftio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

static int	load_header(t_header *header, int fd)
{
	uint32_t	blbl;
	ft_bzero(header, sizeof(t_header));
	read(fd, &header->magic, sizeof(header->magic));//TODO CHECK RETOUR READ
	swap_uint32(&header->magic);
	if (header->magic != COREWAR_EXEC_MAGIC)
		return (-1);
	read(fd, &header->name, sizeof(header->name) - 1);
	read(fd, &header->size, 4);
	read(fd, &header->size, sizeof(header->size));
	swap_uint32(&header->size);
	read(fd, &header->description, sizeof(header->description) - 1);
	read(fd, &blbl, sizeof(blbl));
	return (fd);
}

t_program	*load_program(const char *path, int id)
{
	t_program	*prog;
	int			fd;

	prog = ft_malloc(sizeof(t_program));
	prog->id = id;
	prog->alive = false;
	fd = ft_open(path, O_RDONLY);
	if (load_header(&prog->header, fd) == -1)
		return (NULL);
	prog->program = ft_malloc(prog->header.size * sizeof(uint8_t));
	read(fd, prog->program, prog->header.size * sizeof(uint8_t));
	ft_close(fd);
	return (prog);
}
