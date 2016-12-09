#include "assembler.h"

t_list	*list_add(t_list **list, void const *content, size_t content_size)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return ((*list) = ft_lstnew(content, content_size));
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_lstnew(content, content_size);
	}
	return (*list);
}

char	*get_param_type(t_inst *inst, int i)
{
	if (inst->params[i].type & T_REG)
		return ("register");
	else if (inst->params[i].type & T_DIR)
		return ("direct value");
	return ("indirect value");
}