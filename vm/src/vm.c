/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:40:26 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/20 15:55:02 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "program.h"
#include <fterror.h>
#include <stdint.h>

//thread unsafe
static uint32_t	*param_get_dir(void)
{
	static uint32_t	inds[4] = { 0 };
	static int		i = -1;

	i = i + 1 == 4 ? 0 : i + 1;
	return (&inds[i]);
}

static uint8_t	get_param_pcode(uint8_t pcode, int n)
{
	return (((pcode & (0b11000000 >> (n * 2)))) >> (6 - n * 2));
}

static void	vm_read(t_process *process, void *p, size_t size)
{
	ft_memcpy(p, process->pc, size);
	process->pc += size;
}

static uint32_t	*vm_get_param(t_process *process, uint32_t ptype, uint8_t pcode)
{
	uint32_t	*param;
	uint32_t	temp;

	param = 0;
	if (ptype == T_REG || ((ptype & T_REG) && pcode == REG_CODE))
	{
		vm_read(process, &temp, 1);
		param = &process->reg[temp];
	}
	else if (ptype == T_DIR || ((ptype & T_DIR) && pcode == DIR_CODE))
	{
		vm_read(process, &temp, 2);
		param = param_get_dir();
	}
	else if (ptype == T_IND || ((ptype & T_IND) && pcode == IND_CODE))
	{
		vm_read(process, &temp, 4);
		param = (uint32_t *)&process->pc[temp % MEM_SIZE];
	}
	else
		__builtin_trap();//ft_error_msg("Invalid parameters\n");//todo
	return (param);
}

void		vm_decode_params(t_process *process, t_op *op,
				uint32_t **params)
{
	uint8_t	pcode;
	int		i;

	pcode = 0;
	if (op->has_pcode)
		vm_read(process, &pcode, sizeof(pcode));
	i = 0;
	while (i < op->nb_params)
	{
		params[i] = vm_get_param(process, op->param_types[i], get_param_pcode(pcode, i));
		i++;
	}
}

void		vm_exec(t_vm *vm, t_process *process, uint8_t pid)
{
	uint8_t		op_code;
	t_op		*op;
	uint32_t	*params[3];

	vm_read(process, &op_code, sizeof(op_code));
	if (op_code == 0 || op_code > 16)//TODO DONT HARD CODE
	{
		ft_error_msg("Process %d created by %s tried to execute an illegal instruction %d\n",
						pid, process->owner->header.name, op_code);
	}
	op = &g_op_tab[op_code - 1];
	vm_decode_params(process, op, params);
}

void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t program_id,
				uint8_t *pc)
{
	t_process	process;

	process.carry = false;
	process.owner = prog;
	process.reg[0] = program_id;
	process.pc = pc;
	process.pid = vm->process.size;
	array_add(&vm->process, &process);
	ft_memcpy(vm->memory, prog->program, prog->header.size);
}

t_vm		*vm_new(void)
{
	t_vm	*vm;

	vm = ft_malloc(sizeof(t_vm));
	ft_bzero(vm->memory, sizeof(vm->memory));
	array_init(&vm->programs, sizeof(t_program), 0);
	array_init(&vm->process, sizeof(t_process), 0);
	return (vm);
}
