/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:40:26 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/17 17:24:48 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "program.h"
#include <fterror.h>
#include <ftendianess.h>
#include <stdint.h>
#include <ftio.h>

static uint8_t	get_param_size(t_op *op, uint32_t ptype, uint8_t pcode)
{
	if (op->has_pcode)
	{
		if (pcode == REG_CODE)
			return (1);
		else if ((pcode == DIR_CODE && op->has_idx) || (pcode == IND_CODE))
			return (IND_DATA_SIZE);
		else if (pcode == DIR_CODE && !op->has_idx)
			return (DIR_DATA_SIZE);
		warning("Invalid pcode %x\n", pcode);
	}
	else
	{
		if (ptype == T_REG)
			return (1);
		else if ((ptype == T_DIR && op->has_idx) || (ptype == T_IND))
			return (IND_DATA_SIZE);
		else if (ptype == T_DIR && !op->has_idx)
			return (DIR_DATA_SIZE);
		warning("Invalid ptype %x\n", ptype);
	}
	return (0);
}

static void		get_param_pcode(uint8_t raw_data, uint8_t pcodes[4])
{
	int		i;

	i = 4;
	while (--i >= 0)
	{
		pcodes[i] = raw_data % 4;
		raw_data >>= 2;
	}
}

static void	swap_uint16(uint16_t *n)
{
	*n = (uint16_t)((*n >> 8) | (*n << 8));
}

static void		vm_read(t_process *process, void *p, size_t size)
{
	//TODO handle signed
	debug("        Read %d bytes at position 0x%X", size, process->pc);
	if (size == 0)
	{
		debug("\n");
		return ;
	}

	ft_memcpy(p, process->pc, size);
	if (size == 2)
	{
		swap_uint16(p);
		debug(" raw data = 0x%X\n", *((uint16_t*)p));
	}
	else if (size == 4)
	{
		swap_uint32(p);
		debug(" raw data = 0x%X\n", *((uint32_t*)p));
	}
	else
	{
		debug(" raw data = 0x%X\n", *((uint8_t*)p));
	}

	process->pc += size;
}

static int32_t	*vm_get_param(t_process *process, t_op *op, uint32_t index, uint8_t pcode)
{
	int32_t	*param;
	int32_t	temp;
	int32_t	ptype;

	param = 0;
	temp = 0;
	ptype = op->param_types[index];
	debug(">>  Reading parameter size\n");
	vm_read(process, &temp, get_param_size(op, ptype, pcode));
	if ((ptype == T_REG || ((ptype & T_REG) && pcode == REG_CODE)) && temp <= REG_NUMBER)
	{
		param = (int32_t *)&process->reg[temp];
	}
	else if (ptype == T_DIR || ((ptype & T_DIR) && pcode == DIR_CODE))
	{
		// FIXME: confusing, handle parameter directly in opcode functions?
		param = (int32_t *)&process->pc[temp % MEM_SIZE]; //TODO tous les op ont pas de mod
	}
	else if (ptype == T_IND || ((ptype & T_IND) && pcode == IND_CODE))
	{
		// FIXME: confusing, handle parameter directly in opcode functions?
		param = (int32_t *)&process->pc[temp % IDX_MOD];
	}
	else
		__builtin_trap();//ft_error_msg("Invalid parameters\n");//todo
	return (param);
}

void		vm_decode_params(t_process *process, t_op *op, int32_t **params)
{
	uint8_t	pcode;
	uint8_t	param_pcodes[4];
	int		i;

	pcode = 0;
	ft_bzero(param_pcodes, sizeof(uint8_t) * 4);
	if (op->has_pcode)
	{
		debug(">>  Reading pcode\n");
		vm_read(process, &pcode, sizeof(pcode));
		get_param_pcode(pcode, param_pcodes);
	}
	i = 0;
	while (i < op->nb_params)
	{
		params[i] = vm_get_param(process, op, i, param_pcodes[i]);
		i++;
	}
}

void		vm_exec(t_vm *vm, t_process *process)
{
	uint8_t	op_code;
	t_op	*op;
	int32_t	*params[3];

	debug(">>  Reading opcode (PC: 0x%X)\n", process->pc);
	vm_read(process, &op_code, sizeof(op_code));
	if (op_code == 0 || op_code > 16)//TODO DONT HARD CODE
	{
		ft_error_msg("Process %d created by %s tried to execute an illegal instruction %d\n",
						process->pid, process->owner->header.name, op_code);
	}
	op = &g_op_tab[op_code - 1];
	debug("Instruction %s\n", op->name);
	vm_decode_params(process, op, params);
	op->handler(vm, process, params);
}

void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t *pc,
	size_t start)
{
	t_process	process;

	display_prog(prog);
	process.carry = false;
	process.owner = prog;
	process.reg[0] = prog->id;
	process.pc = pc;
	process.pid = vm->process.size;
	array_add(&vm->process, &process);
	ft_memcpy(vm->memory + start, prog->program, prog->header.size);
}

t_vm		*vm_new(void)
{
	t_vm	*vm;

	vm = ft_malloc(sizeof(t_vm));
	vm->lives = 0;
	vm->current_cycle = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	ft_bzero(vm->memory, sizeof(vm->memory));
	info("Virtual memory start at position 0x%X\n", vm->memory);
	array_init(&vm->programs, sizeof(t_program), 0);
	array_init(&vm->process, sizeof(t_process), 0);
	return (vm);
}

void		vm_dump(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%c%x ", vm->memory[i] > 15 ? 0 : '0',vm->memory[i]);
		if (!((i + 1) % 32))
			ft_printf("\n");
		i++;
	}
}
