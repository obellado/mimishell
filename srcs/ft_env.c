/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:03:54 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:07:50 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		printf("%s\n", envp[i++]);
	g_code = 0;
}

void	ft_export_print_2(char **mas)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mas[i] != NULL)
	{
		write(1, "declare -x ", 12);
		while (mas[i][j] != '=')
			write(1, &mas[i][j++], 1);
		write(1, "=\"", 2);
		j++;
		while (mas[i][j] != '\0')
			write(1, &mas[i][j++], 1);
		write(1, "\"\n", 2);
		i++;
		j = 0;
	}
	free(mas);
}

void	ft_export_print_3(char **mas)
{
	int		n;
	int		i;
	int		j;

	n = ft_count_envp(mas);
	i = 0;
	j = n + 1;
	while (i < --j - 1)
	{
		while (i < n - 1)
		{
			if ((ft_strcmp(mas[i], mas[i + 1])) > 0)
				ft_swap_env(mas, i);
			i++;
		}
		i = 0;
	}
}

void	ft_export_print(char **en)
{
	int		n;
	char	**mas;
	int		i;

	i = -1;
	n = ft_count_envp(en);
	mas = (char **)malloc(sizeof(char *) * (n + 1));
	if (mas == NULL)
		return ;
	mas[n] = NULL;
	while (en[++i] != NULL)
		mas[i] = en[i];
	ft_export_print_3(mas);
	ft_export_print_2(mas);
}
