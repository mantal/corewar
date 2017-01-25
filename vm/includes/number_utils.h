/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:08:44 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 14:09:29 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_UTILS_H
# define NUMBER_UTILS_H

# include <stdint.h>
# include <stdbool.h>

intmax_t	bigatoi(const char *str);
bool		is_valid_number(const char *nbr);

#endif
