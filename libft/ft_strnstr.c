/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:19:28 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:30:50 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(*little))
		return ((char *)big);
	while ((i < len) && (big[i] != '\0'))
	{
		if (little[0] == big[i])
		{
			j = 1;
			while (little[j] != '\0' && (little[j] == big[i + j])
				&& (i + j < len))
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
