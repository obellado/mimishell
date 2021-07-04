/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_obellado.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:28:51 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:09:16 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_prompt(int std_out)
{
	char	buf[1001];

	bzero(buf, 1001);
	getcwd(buf, 1000);
	write(std_out, C_C, sizeof(C_C));
	write(std_out, buf, strlen(buf));
	write(std_out, " ~ ", 3);
	write(std_out, C_R, sizeof(C_R));
	bzero(buf, 1001);
}

void	ft_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		g_code = 131;
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_prompt(1);
		g_code = 130;
	}
}

void	ft_do_com(t_com *l, char ***envp, t_p *p)
{
	ft_redirect_4(l->c);
	if (l->c->re_out != 0)
		dup2(l->c->fd_re_out, 1);
	if (l->c->ncom == 1)
		ft_pwd();
	else if (l->c->ncom == 2)
		ft_cd(l->c, envp);
	else if (l->c->ncom == 4)
		ft_env(*envp);
	else if (l->c->ncom == 3)
		ft_echo(l->c);
	else if (l->c->ncom == 5)
		ft_unset(l->c, envp);
	else if (l->c->ncom == 6)
		ft_export(l->c, envp);
	else if (l->c->ncom == 7)
		ft_exit(l, *envp, p);
	if (l->c->re_out != 0)
	{
		dup2(l->c->std_out, 1);
		close(l->c->fd_re_out);
	}
	if (l->c->re_in != 0)
		close(l->c->fd_re_in);
}

void	ft_do_com_in_pipe(t_sh *m, char **envp)
{
	if (m->ncom == 1)
		ft_pwd();
	else if (m->ncom == 2)
		ft_cd(m, &envp);
	else if (m->ncom == 4)
		ft_env(envp);
	else if (m->ncom == 3)
		ft_echo(m);
	else if (m->ncom == 5)
		ft_unset(m, &envp);
	else if (m->ncom == 6)
		ft_export(m, &envp);
	else if (m->ncom == 7)
		ft_exit_child(m, envp);
}

void	ft_do_and_free(t_com *l, char ***en, t_p *p)
{
	size_t		i;

	i = 0;
	if (l->c->split == NULL || l->c->split[0] == NULL)
		return ;
	if (l->c->cpipe == 0 && l->c->ncom != 0)
		ft_do_com(l, en, p);
	else if (l->c->cpipe >= 1)
		ft_pipe_2(l, *en);
	else if (l->c->cpipe == 0)
		ft_exec(l->c, *en);
}
