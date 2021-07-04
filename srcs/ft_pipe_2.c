/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:43:13 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:40 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork(t_com *l, char **envp, int *fd)
{
	l->c->pid = fork();
	if (l->c->pid == 0)
	{
		if (l->c->i == 0)
			ft_first_cmd(l, fd);
		else if (l->c->i > 0 && l->c->i < l->c->cpipe)
			ft_middle_cmd(l, fd);
		else if (l->c->i == l->c->cpipe)
			ft_last_cmd(l, fd);
		ft_exec_2(l->c, envp);
		exit(g_code);
	}
}

int	*ft_pipe(t_com *l)
{
	int		i;
	int		*fd;

	i = 0;
	while (l->back)
		l = l->back;
	while (l->next)
	{
		i++;
		l = l->next;
	}
	while (l->back)
		l = l->back;
	fd = (int *)malloc(sizeof(int) * ((i * 2) + 1));
	if (fd == NULL)
		return (NULL);
	ft_pipe_4(l, fd);
	return (fd);
}

void	ft_pipe_4(t_com *l, int *fd)
{
	int		i;

	i = 0;
	while (i < l->c->cpipe)
	{
		pipe(l->c->fd);
		fd[i * 2] = l->c->fd[0];
		fd[i * 2 + 1] = l->c->fd[1];
		i++;
	}
	fd[i * 2] = 0;
	while (l->back)
		l = l->back;
}
