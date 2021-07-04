/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:40:43 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:27 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_export(char *n, char **en)
{
	int		i;
	int		len;

	i = 0;
	if (n[i] < 65 || (n[i] > 90 && n[i] < 95) || n[i] == 96 || n[i] > 122)
		return (-1);
	i++;
	while (n[i] != '\0' && n[i] != '=')
	{
		if (n[i] < 48 || (n[i] > 57 && n[i] < 65) || (n[i] > 90 && \
		n[i] < 95) || n[i] == 96 || n[i] > 122)
			return (-1);
		i++;
	}
	if (n[i] != '=')
		return (-3);
	len = i;
	i = 0;
	while (en[i] != NULL)
	{
		if ((ft_strncmp(n, en[i], len - 1)) == 0)
			return (i);
		i++;
	}
	return (-2);
}

void	ft_export_2(t_sh *m, char ***en, int i)
{
	char	**new_en;
	char	**tmp;

	new_en = ft_export_add(*en, m->split[i]);
	if (new_en != NULL)
	{
		tmp = *en;
		*en = new_en;
		ft_free_array(tmp);
		g_code = 0;
	}
	else
	{
		write(2, "minishell: malloc:\n", 19);
		g_code = 1;
	}
}

void	ft_export_3(t_sh *m, char ***en, int i, int n)
{
	char	**new_en;
	char	**tmp;

	tmp = *en;
	new_en = NULL;
	new_en = ft_export_re(*en, m->split[i], n);
	if (new_en != NULL)
	{
		tmp = *en;
		*en = new_en;
		ft_free_array(tmp);
		g_code = 0;
	}
	else
	{
		write(2, "minishell: malloc:\n", 19);
		g_code = 1;
	}
}

void	ft_export_4(t_sh *m, int i)
{
	int		j;

	j = 0;
	while (m->split[i][j] != '=' && m->split[i][j] != '\0')
		j++;
	write(2, "minishell: export: not a valid identifier ", 42);
	write(2, m->split[i], j);
	write(2, "\n", 1);
	g_code = 1;
}

void	ft_export(t_sh *m, char ***en)
{
	int		n;
	int		i;
	char	**new_en;
	char	**tmp;

	i = 1;
	tmp = *en;
	new_en = NULL;
	g_code = 0;
	if (m->split[1] == NULL)
		ft_export_print(*en);
	while (m->split[i] != NULL)
	{
		n = ft_check_export(m->split[i], *en);
		if (n == -1)
			ft_export_4(m, i);
		else if (n == -2)
			ft_export_2(m, en, i);
		else if (n >= 0)
			ft_export_3(m, en, i, n);
		i++;
	}
}
