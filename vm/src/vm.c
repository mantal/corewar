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

static uint8_t	get_param_size(t_op *op, uint8_t pcode)
{
	if (pcode == REG_CODE)
		return (1);
	else if ((pcode == DIR_CODE && op->has_idx) || (pcode == IND_CODE))
		return (IND_DATA_SIZE);
	else if (pcode == DIR_CODE && !op->has_idx)
		return (DIR_DATA_SIZE);
	warning("Invalid pcode %x\n", pcode);
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
	debug("        Read %d bytes at position 0x%X", size, process->entry_point + process->position);
	if (size == 0)
	{
		debug("\n");
		return ;
	}

	ft_memcpy(p, process->entry_point + process->position, size);
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
		debug(" raw data = 0x%X\n", *((uint8_t*)p));

	process->position += size;
}

int32_t		vm_get_param(t_process *process, t_op *op, uint8_t pcode)
{
	int32_t	temp;

	temp = 0;
	debug(">>  Reading parameter size\n");
	vm_read(process, &temp, get_param_size(op, pcode));
	return (temp);
}

void		vm_decode_params(t_process *process, t_op *op, t_op_data *param)
{
	uint8_t	pcode;
	int		i;

	pcode = 0;
	if (op->has_pcode)
	{
		debug(">>  Reading pcode\n");
		vm_read(process, &pcode, sizeof(pcode));
		get_param_pcode(pcode, param->param_pcodes);
	}
	else
		get_param_pcode(0x80, param->param_pcodes);
	i = 0;
	while (i < op->nb_params)
	{
		param->params[i] = vm_get_param(process, op, param->param_pcodes[i]);
		i++;
	}
}

void		vm_exec(t_vm *vm, t_process *process)
{
	uint8_t		op_code;
	t_op		*op;
	t_op_data	param;

	process->op_code_pos = process->position;
	debug(">>  Reading opcode (PC: 0x%X)\n", process->entry_point + process->position);
	vm_read(process, &op_code, sizeof(op_code));
	if (op_code == 0 || op_code > 16)//TODO DONT HARD CODE
	{
		vm_dump(vm);
		ft_error_msg("Process %d created by %s tried to execute an illegal instruction %d\n",
						process->pid, process->owner->header.name, op_code);
	}
	op = &g_op_tab[op_code - 1];
	process->current_instruction = op;
	debug("Instruction %s\n", op->name);
	vm_decode_params(process, op, &param);
	if (check_param(process->current_instruction, &param))
		op->handler(vm, process, &param);
	else
		warning("Invalid arguments!\nInstruction skipped!\n");
}

void		vm_new_process(t_vm *vm, const t_program *prog, uint8_t *pc,
	uint32_t start)
{
	t_process	process;

	process.carry = false;
	process.owner = prog;
	ft_bzero(process.reg, sizeof(uint32_t) * REG_NUMBER);
	process.reg[0] = prog->id;
	process.entry_point = pc;
	process.position = start;
	process.pid = vm->process.size;
	array_add(&vm->process, &process);
}

void		vm_fork(t_vm *vm, t_process *process, int16_t pc, int long_mode)
{
	t_process	fork;
	uint32_t	position;
	int			i;

	i = - 1;
	if (long_mode)
		position = ((process->position + pc - 0x3 + MEM_SIZE) % MEM_SIZE);
	else
		position = ((process->position + (pc % IDX_MOD) - 0x3 + MEM_SIZE) % MEM_SIZE);

	fork.carry = process->carry;
	fork.owner = process->owner;
	ft_bzero(fork.reg, sizeof(uint32_t) * REG_NUMBER);
	while (++i < REG_NUMBER)
		fork.reg[i] = process->reg[i];
	fork.entry_point = process->entry_point;
	fork.position = position;
	fork.pid = vm->process.size;
	array_add(&vm->process, &fork);
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

void		process_dump_registers(t_process *process)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
	{
		ft_printf("0X%X: r%d = %u\n", process->reg + i, i, process->reg[i]);
	}
}
