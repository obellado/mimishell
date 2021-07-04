/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:55:05 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:25:15 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	const unsigned char		*ptr_for_arr1;
	const unsigned char		*ptr_for_arr2;

	ptr_for_arr1 = (unsigned char *)arr1;
	ptr_for_arr2 = (unsigned char *)arr2;
	while (n-- > 0)
	{
		if (*ptr_for_arr1++ != *ptr_for_arr2++)
			return (ptr_for_arr1[-1] - ptr_for_arr2[-1]);
	}
	return (0);
}
