/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:06:33 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:45 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe_2(t_com *l, char **envp)
{
	int		*fd;

	fd = ft_pipe(l);
	if (!fd)
		return ;
	while (21)
	{
		ft_fork(l, envp, fd);
		if (l->next)
			l = l->next;
		else
			break ;
	}
	ft_pipe_3(l, fd);
}

void	ft_pipe_3(t_com *l, int	*fd)
{
	int		i;

	i = 0;
	if (l->c->pid != 0)
	{
		while (wait(&l->c->stat) > 0)
		{
			while (i < (l->c->cpipe * 2))
			{
				close(fd[i]);
				i++;
			}
			if (l->back)
				l = l->back;
		}
	}
	free(fd);
}
