/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:36:38 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/26 11:45:34 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "program.h"
#include <ftendianess.h>
#include <fterror.h>
#include <ftio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

static off_t	get_file_size(const char *path)
{
	off_t	size;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error_msg("Can't read champion file %s\n", path);
	size = lseek(fd, 0, SEEK_END);
	close(fd);
	return (size);
}

static char		*get_file_content(const char *path)
{
	int		fd;
	off_t	size;
	char	*res;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error_msg("Can't read champion file %s\n", path);
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if ((res = ft_memalloc(size + 1)))
		read(fd, res, size);
	close(fd);
	return (res);
}

static void		fix_endianess(t_header *header)
{
	swap_uint32(&header->magic);
	swap_uint32(&header->size);
}

static void		check_prgm_size(const char *path, int expected_size,
				int given_size)
{
	if (given_size != expected_size)
		ft_error_msg("File %s has a code size that differ from what its header \
			says (%d bytes != %d bytes)\n", path, given_size, expected_size);
	if (given_size > CHAMP_MAX_SIZE)
		ft_error_msg("File %s has too large a code (%d bytes > %d bytes)\n",
			path, given_size, CHAMP_MAX_SIZE);
}

t_program		*load_program(const char *path, int id)
{
	t_program	*prog;
	char		*content;
	off_t		size;

	size = get_file_size(path);
	if (size < (off_t)sizeof(t_header))
		ft_error_msg("File %s is too small to be a champion\n", path);
	content = get_file_content(path);
	if (!(prog = ft_memalloc(sizeof(t_program))))
		return (NULL);
	ft_memcpy(&prog->header, content, sizeof(t_header));
	fix_endianess(&prog->header);
	if (prog->header.magic != COREWAR_EXEC_MAGIC)
		ft_error_msg("File %s has an invalid header\n", path);
	check_prgm_size(path, size - sizeof(t_header), prog->header.size);
	if (!(prog->program = ft_memalloc(prog->header.size * sizeof(uint8_t))))
		return (NULL);
	ft_memcpy(prog->program, content + sizeof(t_header), prog->header.size
					* sizeof(uint8_t));
	prog->id = id;
	return (prog);
}
