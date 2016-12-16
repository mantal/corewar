/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:56:18 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/16 15:52:21 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "program.h"
# include <libft.h>
# include <stdbool.h>
# include <stdint.h>

# define REGISTER_NUMBER 16
# define REGISTER_SIZE   32

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA  50
# define NBR_LIVE     21
# define MAX_CHECKS   10

typedef struct	s_process
{
	uint8_t			reg[REGISTER_NUMBER][REGISTER_SIZE];
	bool			carry;
	uint8_t			*pc;
	const t_program	*owner;
}				t_process;

typedef struct	s_vm
{
	t_array		*programs;
	t_array		*process;
	uint8_t		memory[MEM_SIZE];
}				t_vm;

t_vm		*vm_new(void);
void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t program_id,
				uint8_t *pc);
void		vm_exec(t_vm *vm, t_process *process, uint8_t pid);

#endif
