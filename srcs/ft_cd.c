/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:21:34 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:07:45 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_change_env(char ***en, char *oldpwd)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = ft_check_export(oldpwd, *en);
	if (i >= 0)
	{
		tmp = *en;
		*en = ft_export_re(*en, oldpwd, i);
		if (*en != NULL)
			ft_free_array(tmp);
		else
			*en = tmp;
	}
	else if (i == -2)
	{
		tmp = *en;
		*en = ft_export_add(*en, oldpwd);
		if (*en != NULL)
			ft_free_array(tmp);
		else
			*en = tmp;
	}
}

void	ft_cd_3(char ***en)
{
	char		pwd_1[1000];
	char		*newpwd_1;

	newpwd_1 = NULL;
	ft_bzero(pwd_1, sizeof(pwd_1));
	getcwd(pwd_1, 1000);
	newpwd_1 = malloc(ft_strlen(pwd_1) + 5);
	if (newpwd_1 == NULL)
		return ;
	newpwd_1[0] = 'P';
	newpwd_1[1] = 'W';
	newpwd_1[2] = 'D';
	newpwd_1[3] = '=';
	newpwd_1[ft_strlen(pwd_1) + 4] = '\0';
	ft_strcpy(&newpwd_1[4], pwd_1);
	ft_cd_change_env(en, newpwd_1);
	free(newpwd_1);
	g_code = 0;
}

void	ft_cd_2(char ***en)
{
	char		*pwd_2;
	char		*oldpwd_1;

	pwd_2 = NULL;
	oldpwd_1 = NULL;
	pwd_2 = ft_getenv_full("PWD", *en);
	oldpwd_1 = malloc(ft_strlen(pwd_2) + 4);
	if (oldpwd_1 == NULL)
		return ;
	oldpwd_1[0] = 'O';
	oldpwd_1[1] = 'L';
	oldpwd_1[2] = 'D';
	ft_strcpy(&oldpwd_1[3], pwd_2);
	ft_cd_change_env(en, oldpwd_1);
	free(oldpwd_1);
	ft_cd_3(en);
}

void	ft_cd(t_sh *m, char ***en)
{
	int			i;
	char		*pwd_2;
	char		*oldpwd_1;

	pwd_2 = NULL;
	oldpwd_1 = NULL;
	if (m->split[1] == NULL)
		oldpwd_1 = ft_getenv("HOME", *en);
	else
		oldpwd_1 = m->split[1];
	errno = 0;
	i = chdir(oldpwd_1);
	if (i == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		g_code = 1;
		return ;
	}
	oldpwd_1 = NULL;
	ft_cd_2(en);
}
