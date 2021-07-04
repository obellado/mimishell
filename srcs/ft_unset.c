/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:38:49 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:27:37 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_unset_2(char **en, int i)
{
	int		n;
	int		j;
	char	**envp;

	j = -1;
	envp = NULL;
	n = ft_count_envp(en);
	envp = (char **)malloc(sizeof(char *) * n);
	envp[--n] = NULL;
	while (++j < i)
	{
		envp[j] = ft_strdup(en[j]);
		if (envp[j] == NULL)
			return (ft_free_array_return(envp, j - 1, en));
	}
	if (j-- == i)
	{
		while (++j < n)
		{
			envp[j] = ft_strdup(en[j + 1]);
			if (envp[j] == NULL)
				return (ft_free_array_return(envp, j - 1, en));
		}
	}
	return (envp);
}

void	ft_unset_3(char ***en, int n)
{
	char	**new_en;
	char	**tmp;

	new_en = NULL;
	new_en = ft_unset_2(*en, n);
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

void	writter_unset(char *str)
{
	write(2, "minishell: unset: `", 19);
	write(2, str, ft_strlen(str));
	write(2, "\': not a valid identifier\n", 26);
}

void	ft_unset(t_sh *m, char ***en)
{
	int		n;
	int		i;
	char	**new_en;

	i = 1;
	new_en = NULL;
	g_code = 0;
	while (m->split[i] != NULL)
	{
		n = ft_check_unset(m->split[i], *en);
		if (n < 0)
		{
			g_code = 1;
			if (n == -1)
				writter_unset(m->split[i]);
			else
				write(2, m->split[i], ft_strlen(m->split[i]));
		}
		else
			ft_unset_3(en, n);
		i++;
	}
}
