/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 14:46:35 by dlancar           #+#    #+#             */
/*   Updated: 2017/01/25 14:01:13 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "ftstring.h"
#include "ftio.h"

static const t_option	*get_option(const t_option *options, const char *option)
{
	int				i;
	int				j;
	const t_option	*res;
	char			*name;

	i = 0;
	while (true)
	{
		res = &options[i];
		if (res->names == NULL)
			return (NULL);
		j = 0;
		while ((name = res->names[j]))
		{
			if (ft_strcmp(name, option) == 0)
				return (res);
			j++;
		}
		i++;
	}
	return (NULL);
}

int						options(const t_option *options, int argc,
		const char **argv)
{
	const t_option	*opt;
	int				i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && argv[i][1] == '-'))
			return (i);
		opt = get_option(options, &argv[i][1]);
		if (opt == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "Unknow option: %s\n", argv[i]);
			return (-1);
		}
		if (i + opt->args_n >= argc
				|| (opt->validate && !opt->validate(&argv[i], opt->data)))
		{
			ft_printf_fd(2, "%s\n", opt->usage ? opt->usage : "Invalid option");
			return (-1);
		}
		if (opt->callback)
			opt->callback(&argv[i], opt->data);
		i += 1 + opt->args_n;
	}
	return (i);
}
