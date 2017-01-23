/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:13:53 by bel-baz           #+#    #+#             */
/*   Updated: 2016/12/19 17:13:54 by bel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "load.h"
#include <ftstring.h>
#include <limits.h>
#include <fterror.h>
#include "libft.h"
#include <ftio.h>

intmax_t	ft_bigatoi(const char *str)
{
	char		negate;
	intmax_t	rtn;
	intmax_t	i;

	rtn = 0;
	i = 0;
	negate = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		negate = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		rtn *= 10;
		if (negate)
			rtn -= str[i] - 48;
		else
			rtn += str[i] - 48;
		i++;
	}
	return (rtn);
}

char	is_valid_number(char *nbr)
{
	int			i;
	intmax_t	tmp;

	i = 0;
	if (nbr[0] == '-' && ft_strlen(nbr) >= 11)
		return (false);
	if (nbr[0] != '-' && ft_strlen(nbr) >= 10)
		return (false);
	tmp = ft_bigatoi(nbr);
	if (tmp > INT_MAX || tmp < INT_MIN)
		return (false);
	while (nbr[i])
	{
		if ((nbr[i] >= '0' && nbr[i] <= '9') || (i == 0 && nbr[0] == '-'))
		{
			i++;
			continue ;
		}
		else
			return (false);
	}
	return (true);
}

static int getfree(t_array champions)
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
		while (i < champions.size)
		{
			if (((t_program*)array_get(&champions, i))->id == rtn && (found = false))
				break ;
			i++;
		}
		if (!found)
			rtn++;
	}
	return (found);
}

static void parse_champions(int argc, char **argv, t_vm *vm)
{
	int		i;
	int		id;
	char	input_id;
	char	check_id;

	i = 0;
	id = 0;
	check_id = false;
	input_id = false;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-n") && !check_id)
			check_id = true;
		else if (check_id)
		{
			if (is_valid_number(argv[i]))
			{
				check_id = false;
				id = ft_atoi(argv[i]);
				input_id = true;
			}
			else
				ft_error_msg("Invalid champion id %s\n", argv[i]);
		}
		else
		{
			ft_putstr(argv[i]);
			ft_putstr("\n");
			array_add(&vm->programs, load_program(argv[i], !input_id
				? getfree(vm->programs) : id));
			input_id = false;
		}
		i++;
	}
}

void parse_args(int argc, char **argv, t_vm *vm)
{
	if (argc >= 2)
	{
		if (ft_strequ("-dump", argv[0]))
		{
			if (is_valid_number(argv[1]))
			{
				vm->max_cycles = ft_atoi(argv[1]);
				parse_champions(argc - 2, argv + 2, vm);
			}
			else
				ft_error_msg("Invalid dump cycles specifier %s\n", argv[1]);
		}
		else
			ft_error_msg("No dump specifier found! %s is invalid.\n", argv[0]);
	}
	else
		ft_error_msg("No dump cycles specifier found!\n");
}
