/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:58:55 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:18:30 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) - start > len)
		a = malloc(len + 1);
	else
		a = malloc(ft_strlen(s) - start + 1);
	if (!a)
		return (NULL);
	while (len > 0 && s[j] != '\0')
	{
		if (j >= start)
		{
			a[i++] = s[start++];
			len--;
		}
		j++;
	}
	a[i] = '\0';
	return (a);
}
