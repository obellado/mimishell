#include "../minishell.h"

char	*dollar(char *line, char **envp)
{
	int	num_of_valid_dollars;
	int	i;

	i = 0;
	num_of_valid_dollars = dollar_counter(line);
	while (i < num_of_valid_dollars)
	{
		line = dollar_estimator(line, envp);
		i++;
	}
	return (line);
}

int	is_dollar(char *line, int i)
{
	if (line[i] == '$' && line[i + 1] == '?')
		return (1);
	if (line[i] == '$' && !(is_env(&line[i + 1])))
		return (0);
	if (line[i] == '$' && line[i - 1] != '\\' && !is_in_single_quote(line, i))
		return (1);
	return (0);
}

int	is_env(char *new)
{
	int	i;

	i = 0;
	if (new[i] < 65 || (new[i] > 90 && new[i] < 95) || new[i] == 96 || \
	new[i] > 122)
		return (i);
	i++;
	while (new[i] != '\0' && new[i] != '\n')
	{
		if (new[i] < 48 || (new[i] > 57 && new[i] < 65) || (new[i] > 90 && \
		new[i] < 95) || new[i] == 96 || new[i] > 122)
			return (i);
		else
			i++;
	}
	return (i);
}

int	dollar_counter(char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (is_dollar(line, i))
			counter++;
		i++;
	}
	return (counter);
}
