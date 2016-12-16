#include "vm.h"

void op_live(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_ld(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_st(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_add(t_vm *vm, t_process *process, uint_32 *args)
{
    process->reg[args[2]] = process->reg[args[0]] + process->reg[args[1]];
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_sub(t_vm *vm, t_process *process, uint_32 *args)
{
    process->reg[args[2]] = process->reg[args[0]] - process->reg[args[1]];
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_and(t_vm *vm, t_process *process, uint_32 *args)
{
    process->reg[args[2]] = process->reg[args[0]] & process->reg[args[1]]; 
    process->carry = process->reg[args[2]] == 0 ? 1 : 0; 
}

void op_or(t_vm *vm, t_process *process, uint_32 *args)
{
    process->reg[args[2]] = process->reg[args[0]] | process->reg[args[1]]; 
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_xor(t_vm *vm, t_process *process, uint_32 *args)
{
    process->reg[args[2]] = process->reg[args[0]] ^ process->reg[args[1]]; 
    process->carry = process->reg[args[2]] == 0 ? 1 : 0;
}

void op_zjmp(t_vm *vm, t_process *process, uint_32 *args)
{
    if (process->carry == 1)
        process->pc = args[0];
}

void op_ldi(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_sti(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_fork(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_lld(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_lldi(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_lfork(t_vm *vm, t_process *process, uint_32 *args)
{

}

void op_aff(t_vm *vm, t_process *process, uint_32 *args)
{

}