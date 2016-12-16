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
# include "op.h"

typedef struct	s_program
{
	t_header		header;
	uint8_t			*program;
}				t_program;

#endif
