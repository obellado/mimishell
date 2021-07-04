/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:35:22 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:48 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char		*buf;
	size_t		n;

	n = 1000;
	buf = malloc(n + 1);
	if (!buf)
		return ;
	getcwd(buf, n);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	g_code = 0;
}
