/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:18:14 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:23 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_com *l, char **envp, t_p *p)
{
	int		ret;

	ret = 0;
	if (l->c->split[1] != NULL)
		ret = ft_atoi(l->c->split[1]);
	ft_free_history(p);
	ft_free_t_com(l);
	ft_free(envp, ft_count_array(envp));
	g_code = ret;
	exit(ret);
}

void	ft_exit_child(t_sh *m, char **envp)
{
	int		ret;

	ret = 0;
	if (m->split[1] != NULL)
		ret = ft_atoi(m->split[1]);
	ft_free_array(envp);
	exit(ret);
}
