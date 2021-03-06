/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftendianess.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 16:43:40 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/19 09:38:17 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTENDIANESS_H
# define FTENDIANESS_H

# include "libft.h"
# include <stdint.h>
# include <stddef.h>

# ifdef __APPLE__
#  include <libkern/OSByteOrder.h>
#  define SWAP_16(x) (OSSwapConstInt16(x))
#  define SWAP_32(x) (OSSwapConstInt32(x))
#  define SWAP_64(x) (OSSwapConstInt64(x))
# elif __WIN32__
#  define SWAP_16(x) (TODO)
# elif __linux__ || __unix__
# endif

void	swap_uint32(uint32_t *i);

#endif
