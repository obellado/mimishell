#include "../minishell.h"

void	*allocator(t_p *p, void *a)
{
	ft_lstadd_back_p(&p, ft_lstnew_p(a));
	return (a);
}

int	redirect_estimator(t_list_2l *list_for_args)
{
	int		ret;

	ret = 0;
	if (!ft_strncmp(">>", list_for_args->content, 3))
		ret = 1;
	else if (!ft_strncmp(">", list_for_args->content, 2))
		ret = 2;
	else if (!ft_strncmp("<", list_for_args->content, 2))
		ret = 3;
	if (ret != 0 && !(list_for_args->next))
		return (-1);
	else if (ret != 0 && list_for_args->next)
		list_for_args = list_for_args->next;
	return (ret);
}

char	**my_realloc(char **a, int s)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(char *) * (s + 1));
	if (!arr)
		return (NULL);
	while (a[i])
	{
		arr[i] = a[i];
		i++;
	}
	free(a);
	return (arr);
}

void	prs_init(t_parser *prs)
{
	prs->i = 0;
	prs->j = 0;
	prs->numb_cmd = 0;
	prs->list_for_commands = NULL;
	prs->node_for_commands = NULL;
}

void	writter(char *str)
{
	write(2, "minishell: command not found: ", 30);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
