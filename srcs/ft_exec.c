/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:06:08 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:21 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_4(t_sh *m)
{
	if (m->re_in > 0)
	{
		dup2(m->fd_re_in, 0);
		close(m->fd_re_in);
	}
	if (m->re_out > 0)
	{
		dup2(m->fd_re_out, 1);
		close(m->fd_re_out);
	}
}

void	ft_rec_code(int stat)
{
	if (stat == 0)
		g_code = 0;
	else if (stat < 0)
		g_code = 255;
	else if (stat > 1 && stat < 10)
		g_code = 128 + stat;
	else
		g_code = stat / 256;
}

void	ft_exec(t_sh *m, char **envp)
{
	m->pid = fork();
	if (m->pid == -1)
		return ;
	if (m->pid == 0)
	{
		ft_redirect_4(m);
		ft_exec_4(m);
		ft_exec_2(m, envp);
	}
	if (m->pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&m->stat);
		ft_rec_code(m->stat);
	}
}

void	ft_exec_3(t_sh *m, char **envp)
{
	int		r;

	errno = 0;
	r = open(m->split[0], S_IEXEC);
	if (r > 0)
	{
		close(r);
		execve(m->split[0], m->split, envp);
		exit(1);
	}
	else
	{
		r = ft_search(m, envp);
		if (r > 0)
		{
			execve(m->split[0], m->split, envp);
			exit(1);
		}
		if (r <= 0)
		{
			writter(m->split[0]);
			exit(127);
		}
	}
}

void	ft_exec_2(t_sh *m, char **envp)
{
	DIR		*dirp;

	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (m->ncom != 0)
	{
		ft_do_com_in_pipe(m, envp);
		exit(g_code);
	}
	else
	{
		dirp = opendir(m->split[0]);
		if (dirp != NULL)
		{
			write(2, "minishell: ", 11);
			write(2, m->split[0], ft_strlen(m->split[0]));
			write(2, ": is a directory\n", 17);
			closedir(dirp);
			exit(126);
		}
		ft_exec_3(m, envp);
	}
}
