/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:52:54 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:31:20 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	if (n < 0)
		n = -n;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		n_copy;
	int		count;

	n_copy = n;
	count = 0;
	count = ft_count(n_copy);
	arr = malloc(count + 1);
	if (!arr)
		return (NULL);
	arr[count] = '\0';
	if (n < 0)
		arr[0] = '-';
	if (n == 0)
		arr[0] = '0';
	while (ft_abs(n))
	{
		count--;
		arr[count] = 48 + ft_abs(n % 10);
		n /= 10;
	}
	return (arr);
}
