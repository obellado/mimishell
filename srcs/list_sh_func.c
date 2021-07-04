#include "../minishell.h"

void	ft_free_list(t_list_2l *l)
{
	t_list_2l	*tmp;

	tmp = NULL;
	if (l == NULL)
		return ;
	while (l->next)
		l = l->next;
	while (21)
	{
		tmp = l->back;
		free(l->content);
		free(l);
		if (tmp)
			l = tmp;
		else
			break ;
	}
}

t_com	*ft_lstlast_sh(t_com *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_sh(t_com **lst, t_com *new)
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

t_com	*ft_lstnew_sh(void)
{
	t_com	*new_node;
	t_sh	*sh;

	new_node = malloc(sizeof(t_com));
	sh = malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	if (!new_node)
		return (NULL);
	ft_setup_m(sh);
	new_node->c = sh;
	new_node->back = NULL;
	new_node->next = NULL;
	return (new_node);
}
