/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:02:14 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:26 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_free_array_return(char **envp, int index, char **ret)
{
	write(2, "minishell: malloc: error\n", 25);
	ft_free(envp, index);
	return (ret);
}

char	**ft_export_add(char **en, char *new)
{
	int		n;
	int		j;
	char	**envp;

	j = 0;
	envp = NULL;
	n = ft_count_envp(en);
	envp = (char **)malloc(sizeof(char *) * (n + 2));
	if (envp == NULL)
		return (en);
	envp[n + 1] = NULL;
	while (j < n)
	{
		envp[j] = ft_strdup(en[j]);
		if (envp[j] == NULL)
			return (ft_free_array_return(envp, j - 1, en));
		j++;
	}
	envp[n] = ft_strdup(new);
	if (envp[n] == NULL)
		return (ft_free_array_return(envp, n - 1, en));
	return (envp);
}

char	**ft_export_re(char **en, char *new, int i)
{
	int		j;
	char	**envp;

	j = -1;
	envp = NULL;
	envp = (char **)malloc(sizeof(char *) * (ft_count_envp(en) + 1));
	if (envp == NULL)
		return (NULL);
	envp[ft_count_envp(en)] = NULL;
	while (++j < i)
	{
		envp[j] = ft_strdup(en[j]);
		if (envp[j] == NULL)
			return (ft_free_array_return(envp, j - 1, en));
	}
	envp[j] = ft_strdup(new);
	if (envp[j] == NULL)
		return (ft_free_array_return(envp, j - 1, en));
	while (++j < ft_count_envp(en))
	{
		envp[j] = ft_strdup(en[j]);
		if (envp[j] == NULL)
			return (ft_free_array_return(envp, j - 1, en));
	}
	return (envp);
}
