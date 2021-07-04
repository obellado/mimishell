#include "../minishell.h"

int	is_in_single_quote(char *line, int index_dollar)
{
	int	i;
	int	flag_for_single_quote;

	i = 0;
	flag_for_single_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && line[i - 1] != '\\')
			flag_for_single_quote++;
		if (flag_for_single_quote == 2)
			flag_for_single_quote = 0;
		if (i == index_dollar)
			return (flag_for_single_quote);
		i++;
	}
	return (flag_for_single_quote);
}

char	*line_changer(char *line, int index_of_redirect, char *rtp)
{
	char	*ret_line;
	int		i;
	int		j;

	ret_line = malloc(ft_strlen(line) + 3);
	i = 0;
	j = 0;
	while (i < index_of_redirect)
	{
		ret_line[i] = line[i];
		i++;
	}
	ret_line[i] = ' ';
	i++;
	while (rtp[j])
		ret_line[i++] = rtp[j++];
	ret_line[i] = ' ';
	i++;
	j = i;
	i = i - 2;
	while (line[i])
		ret_line[j++] = line[i++];
	ret_line[j] = '\0';
	free(line);
	return (ret_line);
}

char	*redirect_changer(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && (line[i - 1] != ' ' || line[i + 1] != ' '))
		{
			line = line_changer(line, i, "<");
			i += 2;
		}
		else if (line[i] == '>' && line[i + 1] == '>'
			&& line[i - 1] != ' ' && line[i + 2] != ' ')
		{
			line = line_changer(line, i, ">>");
			i += 3;
		}
		else if (line[i] == '>' && line[i - 1] != ' ' && line[i + 1] != ' ')
		{
			line = line_changer(line, i, ">");
			i += 2;
		}
		i++;
	}
	return (line);
}
