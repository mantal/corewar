/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:56:18 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/20 17:45:53 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "program.h"
# include <libft.h>
# include <stdbool.h>
# include <stdint.h>

# define REG_NUMBER 16
# define REG_SIZE   32

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA  50
# define NBR_LIVE     21
# define MAX_CHECKS   10

typedef struct	s_process
{
	uint32_t		reg[REG_NUMBER];//TODO? REG_SIZE EST HARDCODE PARTOUT
	bool			carry;
	uint8_t			*pc;
	unsigned int	pid;
	const t_program	*owner;
}				t_process;

typedef struct	s_vm
{
	t_array		programs;
	t_array		process;
	uint8_t		memory[MEM_SIZE];
	int			current_cycle;
	int			max_cycles;
	int			lives;
	int			cycles_to_die;
	int			next_die;
}				t_vm;

t_vm		*vm_new(void);
void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t *pc);
void		parse_args(int argc, char **argv, t_vm *vm);
void		live(t_program *prg, t_vm *vm);
void		tick_cycles(t_vm *vm);
void		vm_exec(t_vm *vm, t_process *process);
#endif
