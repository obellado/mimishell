#include "../minishell.h"

int	arg_slicer(t_ap *ap)
{
	while (21)
	{
		if (redirect_estimator(ap->list_for_args) > 0)
			ap->i -= 2;
		else if (redirect_estimator(ap->list_for_args) < 0)
		{
			printf("minishell: syntax error near unexpected token \'%s\'\n",
				ap->list_for_args->content);
			ft_free_list(ap->list_for_args);
			return (0);
		}
		if (ap->list_for_args->next)
			ap->list_for_args = ap->list_for_args->next;
		else
			break ;
	}
	ap->list_for_args = ap->tmp;
	if (ap->i == 0)
	{
		ft_free_list(ap->list_for_args);
		return (0);
	}
	return (1);
}

void	ap_init(t_ap *ap, char *line, char **envp)
{
	ap->words_counter = 0;
	line = redirect_changer(line);
	line = dollar(line, envp);
	ap->list_for_args = word_split(line);
	free(line);
	while (ap->list_for_args)
	{
		ap->tmp = ap->list_for_args;
		ap->words_counter++;
		ap->list_for_args = ap->list_for_args->back;
	}
}

void	arg_copy(t_ap *ap, t_com *list_for_commands)
{
	while (ap->i < ap->words_counter)
	{
		if (redirect_estimator(ap->list_for_args) > 0)
		{
			redirect_to_struct(list_for_commands, ap->list_for_args);
			ap->list_for_args = ap->list_for_args->next;
		}
		else
		{
			ap->args[ap->i] = ft_strdup(ap->list_for_args->content);
			ap->i = ap->i + 1;
		}
		ap->args[ap->i] = NULL;
		if (ap->list_for_args->next)
			ap->list_for_args = ap->list_for_args->next;
		else
			break ;
	}
}

char	**arg_prepare(t_com *list_for_commands, char *line, char **envp)
{
	t_ap	ap;

	ap_init(&ap, line, envp);
	if (ap.words_counter == 0)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (NULL);
	}
	ap.list_for_args = ap.tmp;
	ap.i = ap.words_counter;
	if (arg_slicer(&ap) == 0)
		return (NULL);
	ap.args = malloc(sizeof(char *) * (ap.i + 1));
	if (ap.args == NULL)
		return (NULL);
	ap.args[ap.i] = NULL;
	ap.i = 0;
	arg_copy(&ap, list_for_commands);
	ft_free_list(ap.list_for_args);
	return (ap.args);
}
