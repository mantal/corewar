/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:13:53 by bel-baz           #+#    #+#             */
/*   Updated: 2017/01/25 14:25:45 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include "number_utils.h"
#include <ftstring.h>
#include <args.h>
#include <fterror.h>
#include <libft.h>
#include <ftio.h>

static int	get_new_program_id(t_array *champions)
{
	int		rtn;
	char	found;
	size_t	i;

	rtn = 0;
	found = false;
	while (!found)
	{
		i = 0;
		found = true;
		while (i < champions->size)
		{
			if (((t_program *)array_get(champions, i))->id == rtn && (found = false))
				break ;
			i++;
		}
		if (!found)
			rtn++;
	}
	return (rtn);
}

static void	set_verbose_level(const char **args, void *data)
{
	(void)data;
	if (args[0][1] == 'v')
		g_ftio_verbose_level = FTIO_VERBOSE;
	if (args[0][1] == 'd')
		g_ftio_verbose_level = FTIO_DEBUG;
	if (args[0][1] == 'q')
		g_ftio_verbose_level = FTIO_NONE;
}

static void	args_dump(const char **args, void *data)
{
	t_vm	*vm;

	vm = data;
	vm->max_cycles = ft_atoi(args[1]);
}

static bool	args_dump_validate(const char **args, void *data)
{
	(void)data;
	return (is_valid_number(args[1]));
}

static void	args_n(const char **args, void *data)
{
	t_program	*prog;

	prog = load_program(args[2], ft_atoi(args[1]));
	array_add(&((t_vm *)data)->programs, prog);
}

static bool	args_n_validate(const char **args, void *data)
{
	(void)data;
	return (is_valid_number(args[1]));
}

void		parse_args(int argc, const char **argv, t_vm *vm)
{
	t_program		*prog;
	int				i;
	const t_option	opts[] =
	{
		{ .names = (char *[]) { "q", "v", "d", NULL },
				.callback = &set_verbose_level },
		{ .names = (char *[]) { "n", NULL }, .args_n = 2, .callback = &args_n,
				.validate = &args_n_validate, .data = vm },
		{ .names = (char *[]) { "dump", NULL }, .args_n = 1,
				.callback = &args_dump, .validate = &args_dump_validate,
				.data = vm },
		{ .names = NULL }
	};

	i = options(opts, argc, argv);
	if (i < 0)
		ft_error_msg("Usage: corewar [-dvq] [-dump cycles] [-n id] champion\n");
	while (i < argc)
	{
		prog = load_program(argv[i], get_new_program_id(&vm->programs));
		array_add(&vm->programs, prog);
		ft_printf("%d\n", prog->id);
		i++;
	}
}
