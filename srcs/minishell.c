#include "../minishell.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	history_line_loop(t_shell *shell, char ***envp,
		t_p *p, struct termios *term2)
{
	int	l;

	l = 0;
	while (1)
	{
		l = read(0, shell->buff, 9000);
		shell->buff[l] = 0;
		if (ft_strnstr(shell->buff, "\e[A", 9000))
			ft_up(shell, p);
		else if (ft_strnstr(shell->buff, "\e[B", 9000))
			ft_down(shell, p);
		else if (ft_strnstr(shell->buff, "\177", 9000))
			ft_delete(shell);
		else
			ft_writer(shell, p);
		if (ft_strrchr(shell->buff, '\n'))
		{
			ft_enter(shell, envp, p, term2);
			break ;
		}
		if (ft_strrchr(shell->buff, '\4'))
			parser_caller("exit", envp, p, term2);
	}
}

void	shell_loop(struct termios term[2], t_shell *shell, char ***envp, t_p *p)
{
	t_list_2l	*node;

	shell->flag_for_list = 0;
	shell->flag_for_el = 0;
	shell->tmp = allocator(p, ft_calloc(1, 1));
	while (21)
	{
		tcsetattr(0, TCSANOW, &term[0]);
		shell->tmp = allocator(p, ft_calloc(1, 1));
		if (shell->flag_for_el == 0)
		{
			node = allocator(p, ft_lstnew_2l(shell->tmp, NULL));
			ft_lstadd_back_2l(&(shell->list), node);
		}
		shell->flag_for_list = 0;
		shell->flag_for_el = 0;
		ft_prompt(1);
		tputs(save_cursor, 1, ft_putchar);
		ft_memset(shell->buff, 0, 9000);
		shell->tmp = allocator(p, ft_calloc(1, 1));
		shell->tmp = allocator(p, ft_calloc(1, 1));
		history_line_loop(shell, envp, p, &term[1]);
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
	}
}

void	init_params(t_p *p, t_shell *shell, int ac, char **av)
{
	(void)ac;
	(void)av;
	p->address = NULL;
	p->back = NULL;
	p->next = NULL;
	g_code = 0x0;
	shell->list = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell			shell;
	t_p				p;
	struct termios	term[2];
	char			**en;

	init_params(&p, &shell, ac, av);
	en = ft_copy_envp(envp);
	if (en == NULL)
	{
		printf("minishell: malloc: error\n");
		return (1);
	}
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	tcgetattr(0, &term[0]);
	tcgetattr(0, &term[1]);
	term[0].c_lflag &= ~(ECHO);
	term[0].c_lflag &= ~(ICANON);
	term[0].c_cc[VMIN] = 1;
	term[0].c_cc[VTIME] = 0;
	tgetent(0, "xterm-256color");
	if (!isatty(STDIN_FILENO))
		return (1);
	shell_loop(term, &shell, &en, &p);
}
