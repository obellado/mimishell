/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:21:53 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:07:48 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_sh *m)
{
	int		len;
	int		i;

	i = 1;
	if (!ft_strcmp(m->split[i], "-n"))
	{
		m->flag = 1;
		i++;
	}
	while (m->split[i] != NULL)
	{
		len = ft_strlen(m->split[i]);
		write(1, m->split[i], len);
		write(1, " ", 1);
		i++;
	}
	if (m->flag == 0)
		write(1, "\n", 1);
	g_code = 0;
}
