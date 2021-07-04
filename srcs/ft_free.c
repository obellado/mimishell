/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:35:16 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:31 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char **arr)
{
	int		i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
		i++;
	i--;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

int	ft_count_array(char **split)
{
	int		i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

void	ft_free_t_sh(t_sh *m)
{
	if (m->split != NULL)
		ft_free_array(m->split);
	if (m->filename_in != NULL)
		free(m->filename_in);
	if (m->filename_out != NULL)
		free(m->filename_out);
}

void	ft_free_t_com(t_com *l)
{
	t_com	*tmp;

	tmp = NULL;
	while (l->next)
	{
		l = l->next;
	}
	while (21)
	{
		tmp = l->back;
		ft_free_t_sh(l->c);
		free(l->c);
		free(l);
		if (tmp)
			l = tmp;
		else
			break ;
	}
}

void	ft_free_history(t_p *p)
{
	while (p)
	{
		free(p->address);
		p = p->back;
		free(p);
	}
}
