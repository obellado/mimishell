/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:42:23 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:42 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_cmd(t_com *l, int *fd)
{
	int		i;

	i = 0;
	while (i < (l->c->cpipe * 2))
	{
		if (i != 1)
			close(fd[i]);
		i++;
	}
	if (l->c->re_in != 0)
	{
		dup2(l->c->fd_re_out, 1);
		close(l->c->fd_re_out);
	}
	if (l->c->re_out == 0)
		dup2(fd[1], 1);
	else
	{
		dup2(l->c->fd_re_out, 1);
		close(l->c->fd_re_out);
	}
	close(fd[1]);
}

void	ft_middle_cmd(t_com *l, int *fd)
{
	ft_middle_2_cmd(l, fd);
	if (l->c->re_in == 0)
	{
		dup2(fd[(l->c->i - 1) *2], 0);
		close(fd[(l->c->i - 1) *2]);
	}
	if (l->c->re_out == 0)
	{
		dup2(fd[(l->c->i * 2) + 1], 1);
		close(fd[(l->c->i * 2) + 1]);
	}
}

void	ft_middle_2_cmd(t_com *l, int *fd)
{
	int		i;

	i = 0;
	while (i < (l->c->cpipe * 2))
	{
		if (i != (l->c->i - 1) * 2 && i != (l->c->i * 2) + 1)
			close(fd[i]);
		else if (i == (l->c->i - 1) * 2 && l->c->re_in != 0)
		{
			close(fd[i]);
			dup2(l->c->fd_re_in, 0);
			close(l->c->fd_re_in);
		}
		else if (i == (l->c->i * 2) + 1 && l->c->re_out != 0)
		{
			close(fd[i]);
			dup2(l->c->fd_re_out, 1);
			close(l->c->fd_re_out);
		}
		i++;
	}
}

void	ft_last_cmd(t_com *l, int *fd)
{
	ft_last_2_cmd(l, fd);
	if (l->c->re_in == 0)
	{
		dup2(fd[(l->c->i - 1) *2], 0);
		close(fd[(l->c->i - 1) *2]);
	}
	if (l->c->re_out == 0)
		dup2(l->c->std_out, 1);
	else
	{
		dup2(l->c->fd_re_out, 1);
		close(l->c->fd_re_out);
	}
}

void	ft_last_2_cmd(t_com *l, int *fd)
{
	int		i;

	i = 0;
	while (i < (l->c->cpipe * 2))
	{
		if (i != (l->c->i - 1) * 2)
			close(fd[i]);
		else if (i == (l->c->i - 1) * 2 && l->c->re_in != 0)
		{
			close(fd[i]);
			dup2(l->c->fd_re_in, 0);
			close(l->c->fd_re_in);
		}
		i++;
	}
}
