#include "../minishell.h"

int	quote_value(char *quote_line, int ch)
{
	int	i;

	i = 1;
	if (ch == '\'')
	{
		while (quote_line[i] != '\'' && quote_line[i])
			i++;
	}
	if (ch == '\"')
	{
		while (quote_line[i])
		{
			if (quote_line[i] == '\"' && quote_line[i - 1] != '\\')
				break ;
			i++;
		}
	}
	if (quote_line[i] == '\0')
		return (0);
	return (i);
}

char	*quote_word(char *line)
{
	int		i;
	int		len_of_substr;
	char	*str;

	i = 0;
	str = NULL;
	while (line[i])
	{
		if ((line[i] == '\'' && line[i - 1] != '\\')
			|| (line[i] == '\"' && line[i - 1] != '\\'))
		{
			len_of_substr = quote_value(line, line[i]);
			if (len_of_substr == 0)
				printf("no closing quote\n");
			str = ft_substr(line, i + 1, len_of_substr - 1);
			break ;
		}
		i++;
	}
	return (str);
}

void	ft_buffjoin(char *s1, char *s2)
{
	char	*a;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	a = NULL;
	i += ft_strlen(s1);
	while (s2[j] != '\0')
		s1[i++] = s2[j++];
	s1[i] = '\0';
}
