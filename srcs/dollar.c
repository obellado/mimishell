#include "../minishell.h"

int	ret_line_length(char *line, char *env_line, char *dollar_subline)
{
	int	i;
	int	len;
	int	len_for_el;

	if (env_line == NULL)
		len_for_el = 0;
	else
		len_for_el = ft_strlen(env_line);
	if (dollar_subline == NULL)
		len = 0;
	else
		len = ft_strlen(dollar_subline);
	i = ft_strlen(line) - len_for_el + len - 1;
	return (i);
}

void	dollar_init(t_dollar *d)
{
	d->i = 0;
	d->k = 0;
	d->z = 0;
	d->dollar_subline = NULL;
	d->return_line = NULL;
	d->env_line = NULL;
}

void	*dollar_prepare(t_dollar *d, char *line, char **envp)
{
	while (!(is_dollar(line, d->i)))
		d->i++;
	if (line[d->i + 1] == '?')
	{
		d->dollar_subline = ft_itoa(g_code);
		d->j = ft_strlen(d->dollar_subline);
	}
	else
		d->j = is_env(&line[d->i + 1]);
	d->j += d->i + 1;
	d->env_line = ft_substr(line, d->i + 1, (d->j - (d->i + 1)));
	if (d->dollar_subline == NULL)
		d->dollar_subline = ft_getenv(d->env_line, envp);
	d->return_line = malloc(sizeof(char) * \
	(ret_line_length(line, d->env_line, d->dollar_subline) + 1));
	if (d->return_line == NULL)
		return (NULL);
	d->return_line[ret_line_length(line, d->env_line, d->dollar_subline)] = '\0';
	if (d->dollar_subline == NULL)
		d->len_dollar_subline = 0;
	else
		d->len_dollar_subline = ft_strlen(d->dollar_subline);
	return (NULL);
}

char	*dollar_estimator(char *line, char **envp)
{
	t_dollar	d;

	dollar_init(&d);
	dollar_prepare(&d, line, envp);
	while (d.k < ret_line_length(line, d.env_line, d.dollar_subline))
	{
		if (d.k < d.i)
		{
			d.return_line[d.k] = line[d.k];
		}
		else if (d.dollar_subline && d.k >= d.i
			&& d.k < d.i + d.len_dollar_subline)
		{
			d.return_line[d.k] = d.dollar_subline[d.z];
			d.z++;
		}
		else if (d.k > d.i + d.len_dollar_subline - 1)
		{
			d.return_line[d.k] = line[d.j];
			d.j++;
		}
		d.k++;
	}
	free(line);
	return (d.return_line);
}
