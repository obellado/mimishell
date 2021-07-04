/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:06:38 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:35 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		d;

	i = 0;
	d = 0;
	if (s1 == NULL)
		return (-1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			d = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (d);
		}
		i++;
	}
	return (0);
}

void	ft_setup_m(t_sh *m)
{
	m->cpipe = 0;
	m->i = 0;
	m->re_in = 0;
	m->re_out = 0;
	m->fd_re_in = 0;
	m->fd_re_out = 1;
	m->filename_in = NULL;
	m->filename_out = NULL;
	m->split = NULL;
	m->fd[0] = 0;
	m->fd[1] = 1;
	m->stat = 0;
	m->ncom = 0;
	m->flag = 0;
}

int	ft_rec_com(t_sh *m)
{
	int		i;

	i = 0;
	if (ft_strcmp(m->split[i], "pwd\0") == 0)
		m->ncom = 1;
	else if (ft_strcmp(m->split[i], "cd\0") == 0)
		m->ncom = 2;
	else if (ft_strcmp(m->split[i], "echo\0") == 0)
		m->ncom = 3;
	else if (ft_strcmp(m->split[i], "env\0") == 0)
		m->ncom = 4;
	else if (ft_strcmp(m->split[i], "unset\0") == 0)
		m->ncom = 5;
	else if (ft_strcmp(m->split[i], "export\0") == 0)
		m->ncom = 6;
	else if (ft_strcmp(m->split[i], "exit\0") == 0)
		m->ncom = 7;
	else
		m->ncom = 0;
	return (0);
}

void	ft_after_parsing_2(t_sh *m, int std_in, int std_out, int count)
{
	m->std_in = std_in;
	m->std_out = std_out;
	m->cpipe = count;
	ft_rec_com(m);
}

void	ft_after_parsing(t_com **l, char ***envp, t_p *p, int *i)
{
	int		count;
	int		std_in;
	int		std_out;

	if ((*l)->c->split == NULL)
	{
		*i = -20;
		return ;
	}
	if ((*l)->c->split[0] == NULL)
		return ;
	std_in = dup(0);
	std_out = dup(1);
	count = (*l)->c->i;
	ft_after_parsing_2((*l)->c, std_in, std_out, count);
	while ((*l)->back)
	{
		(*l) = (*l)->back;
		ft_after_parsing_2((*l)->c, std_in, std_out, count);
	}
	ft_do_and_free(*l, envp, p);
}
