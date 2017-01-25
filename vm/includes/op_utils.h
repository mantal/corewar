/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:50:02 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 14:54:30 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_UTILS_H
# define OP_UTILS_H

# include "vm.h"
# include <stdint.h>

int32_t	swap_int32(int32_t val);
int		check_param(t_op *op, t_op_data *data);
void	dump_int32(int32_t *param, size_t size);
int		is_register(t_process *process, t_op_data *data, int index);
int		is_indirect(t_process *process, t_op_data *data, int index);
int32_t	*get_register(t_process *process, t_op_data *data, int index);
int32_t	get_value(t_process *process, t_op_data *data, int index);

#endif
