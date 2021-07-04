/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:58:34 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:19 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_copy_envp(char **envp)
{
	int		n;
	int		i;
	char	**en;

	if (envp == NULL)
		return (NULL);
	i = 0;
	n = ft_count_envp(envp);
	en = (char **)malloc(sizeof(char *) * (n + 1));
	if (en == NULL)
		return (NULL);
	en[n] = NULL;
	while (i < n)
	{
		en[i] = ft_strdup(envp[i]);
		if (en[i] == NULL)
		{
			ft_free(en, i - 1);
			return (NULL);
		}
		i++;
	}
	return (en);
}

int	ft_count_envp(char **envp)
{
	int		n;

	n = 0;
	if (envp == NULL)
		return (0);
	while (envp[n] != NULL)
		n++;
	return (n);
}

void	ft_swap_env(char **mas, int	i)
{
	char	*tmp;

	tmp = NULL;
	if (i >= 0)
	{
		tmp = mas[i];
		mas[i] = mas[i + 1];
		mas[i + 1] = tmp;
	}
}

char	*ft_getenv(char *name, char **en)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (en[i] != 0)
	{
		if ((ft_strncmp(name, en[i], len)) == 0)
		{
			if (en[i][len] == '=')
				return (&en[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_getenv_full(char *name, char **en)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (en[i] != 0)
	{
		if ((ft_strncmp(name, en[i], len)) == 0)
		{
			if (en[i][len] == '=')
				return (&en[i][0]);
		}
		i++;
	}
	return (NULL);
}
