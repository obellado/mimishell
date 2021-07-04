/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:55:01 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:32:09 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	const unsigned char		*ptr_to_arr;

	ptr_to_arr = (unsigned char *)arr;
	while (n-- > 0)
	{
		if (*ptr_to_arr == (unsigned char)c)
			return ((void *)ptr_to_arr);
		ptr_to_arr++;
	}
	return (NULL);
}
