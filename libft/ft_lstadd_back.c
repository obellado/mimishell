/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:53:00 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/01 20:26:55 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*begin;

	if (!(new))
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	begin = *lst;
	if (begin)
	{
		while (begin->next)
			begin = begin->next;
	}
	begin->next = new;
}
