/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:31:28 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/13 16:24:34 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include <stdint.h>
# include <stdbool.h>

# define PROG_NAME_LEN 128
# define PROG_DESC_LEN 2048

typedef struct	s_header
{
	unsigned int	magic;
	char			name[PROG_NAME_LEN + 1];
	unsigned int	size;
	char			description[PROG_DESC_LEN + 1];
} 				t_header;

typedef struct	s_program
{
	t_header		header;
	uint8_t			*program;
	int				id;
	bool			alive;
}				t_program;

#endif
