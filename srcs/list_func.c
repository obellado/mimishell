#include "../minishell.h"

void	ft_lstadd_back_2l(t_list_2l **lst, t_list_2l *new)
{
	t_list_2l	*begin;

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

t_list_2l	*ft_lstnew_2l(char *content, t_list_2l *back)
{
	t_list_2l	*new_node;

	new_node = (t_list_2l *)malloc(sizeof(t_list_2l));
	if (!(new_node))
		return (NULL);
	new_node->content = content;
	new_node->back = back;
	new_node->next = NULL;
	return (new_node);
}

t_list_2l	*ft_lstlast_2l(t_list_2l *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_p(t_p **lst, t_p *new)
{
	t_p	*begin;

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

t_p	*ft_lstnew_p(void *content)
{
	t_p	*new_node;

	new_node = malloc(sizeof(t_p));
	if (!(new_node))
		return (NULL);
	new_node->address = content;
	new_node->next = NULL;
	new_node->back = NULL;
	return (new_node);
}
