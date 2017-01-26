/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:30:52 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/26 18:05:55 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIVE_H
# define LIVE_H

int		count_alive(t_vm *vm);
void	print_alive(t_vm *vm);
bool	has_lived(t_vm *vm, int id);
void	live(t_program *prg, t_vm *vm, int startup);
void	tick_cycles(t_vm *vm);
#endif
