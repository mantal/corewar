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
	ft_bzero(header, sizeof(t_header));
	read(fd, &header->magic, sizeof(header->magic));//TODO CHECK RETOUR READ
	swapInt32(&header->magic);
	read(fd, &header->name, sizeof(header->name) - 1);
	read(fd, &header->size, 4);
	read(fd, &header->size, sizeof(header->size));
	swapInt32(&header->size);
	read(fd, &header->description, sizeof(header->description) - 1);
	uint32_t blbl; read(fd, &blbl, sizeof(blbl));
	return (fd);
}

#include <stdio.h>
void		display_prog(t_program *prog)
{
	printf("magic: %x\n", prog->header.magic);//
	printf("name: %s\n", prog->header.name);
	printf("size: %d\n", prog->header.size);//
	printf("desc: %s\n", prog->header.description);//

	for(unsigned int i = 0; i < prog->header.size; i++)
	{
		printf("%02hhx", prog->program[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
		else if ((i + 1) % 2 == 0)
			printf(" ");
	}
}

t_program	*load_program(const char *path)
{
	t_program	*prog;
	int			fd;

	prog = ft_malloc(sizeof(t_program));
	fd = ft_open(path, O_RDONLY);
	load_header(&prog->header, fd);
	prog->program = ft_malloc(prog->header.size * sizeof(uint8_t));
	read(fd, prog->program, prog->header.size * sizeof(uint8_t));
	ft_close(fd);
	return (prog);
}
