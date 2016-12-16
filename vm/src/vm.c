/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:40:26 by dlancar           #+#    #+#             */
/*   Updated: 2016/12/16 16:08:53 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "program.h"
#include <fterror.h>
#include <stdint.h>

#define VM_PARAM_CODE(pcode, n) ((pcode & (1 << i * 2)) | (pcode & (1 << ((i * 2) + 1))))

static void	vm_read(t_vm *vm, t_process *process, void *p, size_t size)
{
	ft_memcpy(p, vm->memory, size);
	process->pc += size;
}

static uint32_t	vm_get_param(t_vm *vm, t_process *process, uint32_t ptype,
				uint32_t pcode)//pcode => int8?
{
	uint32_t	param;
	int32_t		temp;

	if (ptype == T_REG || ((ptype & T_REG) && pcode == REG_CODE))
	{
		vm_read(vm, process, &param, 1);
		param = (uint32_t)process->reg[param];
	}
	else if (ptype == T_DIR || ((ptype & T_DIR) && pcode == DIR_CODE))
	{
		vm_read(vm, process, &param, 2);
		//todo labels????
	}
	else if (ptype == T_IND || ((ptype & T_IND) && pcode == IND_CODE))
	{
		vm_read(vm, process, &temp, 4);
		param = process->pc[temp % MEM_SIZE];
	}
	else
		__builtin_trap();//ft_error_msg("Invalid parameters\n");//todo
	return (param);
}

void		vm_decode_params(t_vm *vm, t_process *process, t_op *op,
				uint32_t *params)
{
	uint32_t	pcode;
	int			i;

	pcode = 0;
	if (op->has_pcode)
		vm_read(vm, process, &pcode, 8);
	i = 0;
	while (i < op->nb_params)
	{
		params[i] = vm_get_param(vm, process, op->param_types[i], VM_PARAM_CODE(pcode, i));
		i++;
	}
}

void		vm_exec(t_vm *vm, t_process *process, uint8_t pid)
{
	uint8_t		op_code;
	t_op		*op;
	uint32_t	params[3];//TODO #define the max params

	vm_read(vm, process, &op_code, sizeof(op_code));
	if (op_code == 0 || op_code > 16)//TODO DONT HARD CODE
	{
		ft_error_msg("Process %d created by %s tried to execute an illegal instruction %d\n",
						pid, process->owner->header.name, op_code);
	}
	op = &g_op_tab[op_code - 1];
	vm_decode_params(vm, process, op, params);
}

void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t program_id,
				uint8_t *pc)
{
	t_process	process;

	process.carry = false;
	process.owner = prog;
	process.reg[0][1] = program_id;
	process.pc = pc;
	array_add(vm->process, &process);
	ft_memcpy(vm->memory, prog->program, prog->header.size);
}

t_vm		*vm_new(void)
{
	t_vm	*vm;

	vm = ft_malloc(sizeof(t_vm));
	ft_bzero(vm->memory, sizeof(vm->memory));
	vm->process = array_new(sizeof(t_process), 0);
	vm->programs = array_new(sizeof(t_program), 0);
	return (vm);
}
