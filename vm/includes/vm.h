/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:56:18 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 14:11:36 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "program.h"
# include "live.h"
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
	uint32_t		reg[REG_NUMBER + 1];
	bool			carry;
	uint8_t			*entry_point;
	uint32_t		position;
	uint32_t		op_code_pos;
	t_op			*current_instruction;
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
void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t *pc,
	uint32_t start);
void		parse_args(int argc, const char **argv, t_vm *vm);
void		live(t_program *prg, t_vm *vm);
void		tick_cycles(t_vm *vm);
void		vm_exec(t_vm *vm, t_process *process);
void		vm_dump(t_vm *vm);
void		process_dump_registers(t_process *process);
int			check_param(t_op *op, t_op_data *data);
void		vm_fork(t_vm *vm, t_process *process, int16_t pc, int long_mode);
void		vm_memread(t_process *process, void *ptr, int pos, size_t size);
void		vm_memwrite(t_process *process, void *ptr, int pos, int32_t size);
#endif
