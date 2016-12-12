#include "assembler.h"

static void		encode_parameter(t_param *param, char *data, int *pos)
{
	int		tmp;

	if (param->required_bytes == 1)
		data[*pos] = param->integer_value;
	else
	{
		if (param->required_bytes == 2)
			tmp = swap_short(param->integer_value);
		else
			tmp = swap_uint(param->integer_value);
		ft_memcpy(data + *pos, &tmp, param->required_bytes);
	}
	(*pos) += param->required_bytes;
}

static void		encode_params(t_inst *inst, char *data, int *pos)
{
	int		i;

	i = 0;
	while (i < g_op_tab[inst->index].nb_params)
	{
		encode_parameter(&inst->params[i], data, pos);
		i++;
	}
}

static char	    encode_opcode_extra(t_inst *inst)
{
	char	res;
	char	param_code;
	int		i;

	i = 0;
	res = 0;
	while (i < 3)
	{
		if (i > g_op_tab[inst->index].nb_params - 1)
			param_code = 0;
		else if (inst->params[i].type & T_REG)
			param_code = REG_CODE;
		else if (inst->params[i].type & T_DIR)
			param_code = DIR_CODE;
		else
			param_code = IND_CODE;
		res |= param_code;
		res <<= 2;
		i++;
	}
	return (res);
}

void	    	encode_inst(t_inst *inst, char *data, int *pos)
{
	data[(*pos)++] = inst->index + 1;
	if (g_op_tab[inst->index].has_pcode)
		data[(*pos)++] = encode_opcode_extra(inst);
	encode_params(inst, data, pos);
}