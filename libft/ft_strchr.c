/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:57:47 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:22:10 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	const char	*ptr_to_str;

	ptr_to_str = str;
	while (*ptr_to_str != '\0')
	{
		if (*ptr_to_str == ch)
			return ((char *)ptr_to_str);
		ptr_to_str++;
	}
	if (*ptr_to_str == ch)
	{
		return ((char *)ptr_to_str);
	}
	return (0);
}
