/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists_of_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:59:34 by obellado          #+#    #+#             */
/*   Updated: 2021/07/04 18:08:33 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_com	*ft_lstnew_com(t_sh *content)
{
	t_com	*new_node;

	new_node = (t_com *)malloc(sizeof(t_com));
	if (!(new_node))
		return (NULL);
	new_node->c = content;
	new_node->next = NULL;
	new_node->back = NULL;
	return (new_node);
}

void	ft_lstadd_back_com(t_com **lst, t_com *new)
{
	t_com	*begin;

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
		{
			begin = begin->next;
		}
	}
	new->back = begin;
	begin->next = new;
	*lst = begin->next;
}
