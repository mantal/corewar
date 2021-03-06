/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/19 16:42:43 by dlancar           #+#    #+#             */
/*   Updated: 2016/01/09 17:05:59 by dlancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fterror.h"
#include "ftio.h"
#include "libft.h"
#include "net.h"

#include <sys/select.h>
#include <sys/resource.h>

static void	select_update(t_socket *soc, int r)
{
	int		i;

	i = 0;
	while (r > 0 && i < soc->fds_size)
	{
		if (FD_ISSET(i, &soc->fd_read) && soc->fds[i].on_read)
			soc->fds[i].on_read(soc, i);
		if (FD_ISSET(i, &soc->fd_write) && soc->fds[i].on_write)
			soc->fds[i].on_write(soc, i);
		if (FD_ISSET(i, &soc->fd_read) || FD_ISSET(i, &soc->fd_write))
			r--;
		i++;
	}
}

void		socket_select(t_socket *soc)
{
	int	i;
	int	r;

	FD_ZERO(&(soc->fd_read));
	FD_ZERO(&(soc->fd_write));
	i = -1;
	soc->nfds = 0;
	while (++i < soc->fds_size)
	{
		if (soc->fds[i].type != SOC_FREE && i != STDOUT)
		{
			FD_SET(i, &(soc->fd_read));
			soc->nfds = i > soc->nfds ? i : soc->nfds;
		}
	}
	r = select(soc->nfds + 1, &soc->fd_read, &soc->fd_write, NULL, NULL);
	if (r < 0)
		;
	select_update(soc, r);
}
