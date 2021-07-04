#include "../minishell.h"

int	parse_spec(t_parser *prs, char *line)
{
	prs->j = prs->i;
	while (line[prs->i] && prs->i < (int)ft_strlen(line))
	{
		if ((line[prs->i] == '\'' && line[prs->i - 1] != '\\')
			|| (line[prs->i] == '\"' && line[prs->i - 1] != '\\'))
		{
			if (quote_value(line + prs->i, line[prs->i]) == 0)
			{
				printf("minishell: syntax error near unexpected token\n");
				return (-20);
			}
			prs->i += quote_value(line + prs->i, line[prs->i]);
		}
		if ((line[prs->i] == '|' && line[prs->i - 1] != '\\')
			|| (line[prs->i] == ';' && line[prs->i - 1] != '\\'))
			break ;
		prs->i++;
	}
	return (0);
}

void	part_of_parser(t_parser *prs, char *line, char ***envp)
{
	t_com	*node;

	node = NULL;
	node = ft_lstnew_sh();
	if (prs->i - prs->j > 0)
		prs->sub_line = ft_substr(line, prs->j, prs->i - prs->j);
	node->c->split = arg_prepare(node, prs->sub_line, *envp);
	if (node->c->split == NULL)
	{
		free(node->c);
		free(node);
		return ;
	}
	node->c->i = prs->numb_cmd++;
	ft_lstadd_back_com(&(prs->list_for_commands), node);
}

int	antinorm(void)
{
	printf("minishell: syntax error near unexpected token\n");
	return (-20);
}

int	parser(char *line, char ***envp, t_p *p)
{
	t_parser	prs;

	prs_init(&prs);
	while (line[prs.i] && line[prs.i] != '\0' && prs.i < (int)ft_strlen(line))
	{
		if (parse_spec(&prs, line) == -20)
			return (-20);
		if (prs.i - prs.j < 1)
			return (antinorm());
		part_of_parser(&prs, line, envp);
		if (line[prs.i] == ';')
		{
			ft_after_parsing(&prs.list_for_commands, envp, p, &prs.i);
			ft_free_t_com(prs.list_for_commands);
			return (prs.i + 1);
		}
		if (line[0] == '\\' && line[1] == '\0')
			return (-20);
		prs.i++;
	}
	ft_after_parsing(&prs.list_for_commands, envp, p, &prs.i);
	ft_free_t_com(prs.list_for_commands);
	return (prs.i);
}

void	parser_caller(char *input_line, char ***envp,
		t_p *p, struct termios *term2)
{
	char	*line;
	int		i;
	int		j;

	tcsetattr(0, TCSANOW, term2);
	line = ft_strtrim(input_line, " ");
	i = 0;
	if (!ft_strcmp(line, "exit"))
		printf("exit\n");
	while (line[i] && i < (int)ft_strlen(line))
	{
		j = parser(&line[i], envp, p);
		if (j < 0)
		{
			break ;
		}
		i += j;
	}
	free(line);
}
