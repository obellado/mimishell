/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:58:28 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/04 21:41:56 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int		index_sum;

	while (n-- > 0 && *str1 && *str2)
	{
		index_sum = ((unsigned char)*str1 - (unsigned char)*str2);
		if (index_sum != 0)
		{
			if (*str1++ != *str2++)
				return (index_sum);
		}
		str1++;
		str2++;
	}
	return (0);
}
