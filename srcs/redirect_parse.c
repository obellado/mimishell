#include "../minishell.h"

void	redirect_3(t_com *list_for_commands, t_list_2l *list_for_args)
{
	list_for_commands->c->re_in = 1;
	list_for_args = list_for_args->next;
	list_for_commands->c->filename_in = ft_strdup(list_for_args->content);
	if (list_for_commands->c->fd_re_in > 0)
		close(list_for_commands->c->fd_re_in);
	errno = 0;
	list_for_commands->c->fd_re_in = open(list_for_commands->c->filename_in,
			O_RDONLY);
	if (list_for_commands->c->fd_re_in == -1)
	{
		write(2, "minishell: ", 11);
		write(2, list_for_commands->c->filename_in,
			ft_strlen(list_for_commands->c->filename_in));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		free(list_for_commands->c->filename_in);
		list_for_commands->c->filename_in = NULL;
	}
}

void	redirect_2(t_com *list_for_commands, t_list_2l *list_for_args)
{
	list_for_commands->c->re_out = 1;
	list_for_args = list_for_args->next;
	if (list_for_commands->c->fd_re_out > 1)
	{
		close(list_for_commands->c->fd_re_out);
		free(list_for_commands->c->filename_out);
		list_for_commands->c->filename_out = NULL;
	}
	list_for_commands->c->filename_out = ft_strdup(list_for_args->content);
	list_for_commands->c->fd_re_out = open(list_for_commands->c->filename_out,
			O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
}

void	redirect_1(t_com *list_for_commands, t_list_2l *list_for_args)
{
	list_for_commands->c->re_out = 2;
	list_for_args = list_for_args->next;
	if (list_for_commands->c->fd_re_out > 1)
	{
		close(list_for_commands->c->fd_re_out);
		free(list_for_commands->c->filename_out);
		list_for_commands->c->filename_out = NULL;
	}
	list_for_commands->c->filename_out = ft_strdup(list_for_args->content);
	list_for_commands->c->fd_re_out = open(list_for_commands->c->filename_out,
			O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
}

void	redirect_to_struct(t_com *list_for_commands, t_list_2l *list_for_args)
{
	int	redirect;

	if (list_for_commands->c->fd_re_in == -1)
		return ;
	redirect = redirect_estimator(list_for_args);
	if (redirect == 3)
		redirect_3(list_for_commands, list_for_args);
	if (redirect == 2)
		redirect_2(list_for_commands, list_for_args);
	if (redirect == 1)
		redirect_1(list_for_commands, list_for_args);
}
