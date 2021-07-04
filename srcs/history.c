#include "../minishell.h"

void	ft_enter(t_shell *shell, char ***envp, t_p *p, struct termios *term2)
{
	if (shell->tmp[0] == '\n' && shell->flag_for_list != 1)
		shell->flag_for_el = 1;
	else if (shell->flag_for_list)
	{
		shell->list->content[ft_strlen(shell->list->content) - 1] = '\0';
		shell->tmp_str = shell->list->content;
		shell->list = ft_lstlast_2l(shell->list);
		shell->list->content = allocator(p, ft_strdup(shell->tmp_str));
		shell->reserve_ptr->content = shell->copy;
	}
	parser_caller(shell->list->content, envp, p, term2);
}

void	ft_up(t_shell *shell, t_p *p)
{
	if (shell && shell->list && shell->list->back != NULL)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (shell->list)
		{
			shell->list = shell->list->back;
			write(1, shell->list->content, ft_strlen(shell->list->content));
			shell->flag_for_list = 1;
		}
	}
	shell->copy = allocator(p, ft_strdup(shell->list->content));
	shell->reserve_ptr = shell->list;
}

void	ft_down(t_shell *shell, t_p *p)
{
	if (shell && shell->list && shell->list->next != NULL)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (shell->list)
		{
			shell->list = shell->list->next;
			write(1, shell->list->content, ft_strlen(shell->list->content));
			shell->flag_for_list = 1;
		}
	}
	shell->copy = allocator(p, ft_strdup(shell->list->content));
	shell->reserve_ptr = shell->list;
}

void	ft_delete(t_shell *shell)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	if (shell->flag_for_list)
	{
		shell->list->content[ft_strlen(shell->list->content) - 1] = '\0';
		write(1, shell->list->content, ft_strlen(shell->list->content));
	}
	else
	{
		if (ft_strlen(shell->tmp) > 0)
			shell->tmp[ft_strlen(shell->tmp) - 1] = '\0';
		write(1, shell->tmp, ft_strlen(shell->tmp));
	}
}

void	ft_writer(t_shell *shell, t_p *p)
{
	shell->tmp = allocator(p, ft_strjoin(shell->tmp, shell->buff));
	if (shell->flag_for_list)
		shell->list->content = allocator(p,
				ft_strjoin(shell->list->content, shell->buff));
	else
	{
		shell->list->content = allocator(p, ft_strdup(shell->tmp));
		shell->list->content[ft_strlen(shell->list->content) - 1] = '\0';
	}
	write(1, shell->buff, ft_strlen(shell->buff));
}
