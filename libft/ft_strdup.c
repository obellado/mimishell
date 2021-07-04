/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:57:51 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:21:40 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*a;
	int		i;

	i = 0;
	a = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!a)
		return (NULL);
	while (str[i] != '\0')
	{
		a[i] = str[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
