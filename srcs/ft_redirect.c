/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:40:18 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:50 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redirect(t_com *l)
{
	int		r;
	char	buf[5];

	if (l->c->re_in == 1)
		l->c->fd_re_in = open(l->c->filename_in, O_RDONLY);
	if (l->c->re_out == 1)
		l->c->fd_re_out = open(l->c->filename_out, O_TRUNC | O_RDWR);
	else if (l->c->re_out == 2)
	{
		l->c->fd_re_out = open(l->c->filename_out, O_RDWR);
		while (21)
		{
			r = read(l->c->fd_re_out, &buf, 5);
			if (r >= 0)
			{
				if (r == 0)
					break ;
			}
		}
	}
}

void	ft_redirect_4(t_sh *m)
{
	if (m->fd_re_in == -1)
	{
		if (m->fd_re_out > 2)
			close(m->fd_re_out);
		exit(1);
	}
}
