#include "../minishell.h"

void	dollar_params_init(t_word_split *w_i)
{
	w_i->list_for_args = NULL;
	w_i->node_for_args = NULL;
	w_i->j = 0;
	w_i->i = 0;
	w_i->buff = malloc(100);
	if (!w_i->buff)
		return ;
}

void	word_maker(t_word_split *w_i, char *line)
{
	while (line[w_i->i])
	{
		if (line[w_i->i] == ' ' && line[w_i->i - 1] != '\\')
		{
			while (line[w_i->i] == ' ')
				w_i->i++;
			break ;
		}
		if (ft_strchr("'\"", line[w_i->i]))
		{
			w_i->tmp = quote_word(line + w_i->i);
			ft_buffjoin(w_i->buff, w_i->tmp);
			w_i->i += ft_strlen(w_i->tmp) + 1;
			w_i->j = ft_strlen(w_i->buff);
			free(w_i->tmp);
		}
		else if (ft_strchr("\\", line[w_i->i]))
		{
			w_i->buff[w_i->j] = line[++w_i->i];
			w_i->j++;
		}
		else
			w_i->buff[w_i->j++] = line[w_i->i];
		w_i->i++;
	}
}

t_list_2l	*word_split(char *line)
{
	t_word_split	w_i;

	dollar_params_init(&w_i);
	while (1)
	{
		w_i.node_for_args = ft_lstnew_2l(NULL, NULL);
		ft_memset(w_i.buff, 0, 100);
		w_i.j = 0;
		word_maker(&w_i, line);
		if (w_i.buff[0] != '\0')
		{
			w_i.node_for_args->content = ft_strdup(w_i.buff);
			ft_lstadd_back_2l(&(w_i.list_for_args), w_i.node_for_args);
		}
		else
			ft_free_list(w_i.node_for_args);
		if (!line[w_i.i] || (line[w_i.i] == ' ' && line[w_i.i - 1] != '\\'))
			break ;
	}
	free(w_i.buff);
	return (w_i.list_for_args);
}
