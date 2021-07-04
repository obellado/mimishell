/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:33:37 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:53 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dest == NULL || src == NULL)
		return (0);
	ft_memcpy(dest, src, src_len + 1);
	return (src_len);
}

int	ft_search_2(t_sh *m, char *pp, DIR *dirp, char *path)
{
	struct dirent	*dp;
	int				len;

	len = ft_strlen(m->split[0]);
	while (21)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break ;
		if (dp->d_namlen == len && ft_strcmp(dp->d_name, m->split[0]) == 0)
		{
			len += ft_strlen(pp);
			ft_strcpy(path, m->split[0]);
			free(m->split[0]);
			m->split[0] = malloc(len + 2);
			ft_strcpy(m->split[0], pp);
			len = ft_strlen(pp);
			m->split[0][len++] = '/';
			while (*path)
				m->split[0][len++] = *path++;
			m->split[0][len] = '\0';
			return (1);
		}
	}
	return (0);
}

int	ft_search(t_sh *m, char **env)
{
	char	*path;
	char	**pp;
	int		i;
	int		r;
	DIR		*dirp;

	i = 0;
	r = 0;
	path = ft_getenv("PATH", env);
	pp = ft_split(path, ':');
	while (pp[i])
	{
		dirp = opendir(pp[i]);
		if (dirp == NULL)
			return (-1);
		r = ft_search_2(m, pp[i], dirp, path);
		(void)closedir(dirp);
		if (r == 1)
			return (1);
		else
			i++;
	}
	ft_free_array(pp);
	return (0);
}
