/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2017/01/25 17:51:24 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdint.h>

# define IND_DATA_SIZE				2
# define REG_DATA_SIZE				4
# define DIR_DATA_SIZE				REG_DATA_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct s_vm			t_vm;
typedef struct s_process	t_process;

typedef struct		s_op_data
{
	uint8_t			param_pcodes[3];
	int32_t			params[3];
}					t_op_data;

typedef void		(*t_op_handler)(t_vm *vm, t_process *process,
				t_op_data *data);

typedef struct		s_op
{
	char			*name;
	int				nb_params;
	unsigned int	param_types[4];
	int				opcode;
	int				nb_cycles;
	char			*desc;
	int				has_pcode;
	int				has_idx;
	t_op_handler	handler;
}					t_op;

extern t_op			g_op_tab[17];

void				op_live(t_vm *vm, t_process *process, t_op_data *data);
void				op_ld(t_vm *vm, t_process *process, t_op_data *data);
void				op_st(t_vm *vm, t_process *process, t_op_data *data);
void				op_add(t_vm *vm, t_process *process, t_op_data *data);
void				op_sub(t_vm *vm, t_process *process, t_op_data *data);
void				op_and(t_vm *vm, t_process *process, t_op_data *data);
void				op_or(t_vm *vm, t_process *process, t_op_data *data);
void				op_xor(t_vm *vm, t_process *process, t_op_data *data);
void				op_zjmp(t_vm *vm, t_process *process, t_op_data *data);
void				op_ldi(t_vm *vm, t_process *process, t_op_data *data);
void				op_sti(t_vm *vm, t_process *process, t_op_data *data);
void				op_fork(t_vm *vm, t_process *process, t_op_data *data);
void				op_lld(t_vm *vm, t_process *process, t_op_data *data);
void				op_lldi(t_vm *vm, t_process *process, t_op_data *data);
void				op_lfork(t_vm *vm, t_process *process, t_op_data *data);
void				op_aff(t_vm *vm, t_process *process, t_op_data *data);

#endif
