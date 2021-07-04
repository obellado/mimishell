/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:51:09 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:31:46 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	int		nbr;

	sign = 1;
	nbr = 0;
	while ((*str == 32) || ((*str >= 9) && (*str <= 13)))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			sign = -1;
		else
			sign = 1;
		str++;
	}
	while (((int)*str >= 48) && (int)*str <= 57)
	{
		nbr = nbr * 10 + ((int)*str - 48);
		str++;
	}
	return (nbr * sign);
}
