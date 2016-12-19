/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2016/12/14 15:46:20 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

//# define IND_SIZE				2
//# define REG_SIZE				4
//# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4//todo mv
# define MEM_SIZE				512//
//# define MEM_SIZE				(4 * 1024)//todo mv
# define IDX_MOD				(MEM_SIZE / 8)//todo mv
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

typedef struct		s_op
{
	char		*name;
	int			nb_params;
	int			param_types[4];
	int			opcode;
	int			nb_cycles;
	char		*desc;
	int			has_pcode;
	int			has_idx;
}					t_op;

extern t_op	g_op_tab[17];

#endif
