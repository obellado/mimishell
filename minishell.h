#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include "libft/libft.h"

# define C_C   "\x1b[36m"
# define C_R   "\x1b[0m"

int		g_code;

typedef struct s_sh
{
	int		i;
	int		cpipe;
	pid_t	pid;
	int		stat;
	int		re_in;
	char	*filename_in;
	int		fd_re_in;
	int		re_out;
	char	*filename_out;
	int		fd_re_out;
	int		fd[2];
	int		std_in;
	int		std_out;
	int		ncom;
	char	**split;
	int		flag;
}				t_sh;

typedef struct s_com
{
	t_sh			*c;
	struct s_com	*next;
	struct s_com	*back;
}				t_com;

typedef struct s_p
{
	void		*address;
	struct s_p	*next;
	struct s_p	*back;
}	t_p;

typedef struct s_list_2l
{
	char				*content;
	struct s_list_2l	*next;
	struct s_list_2l	*back;
}				t_list_2l;

typedef struct s_dollar
{
	char	*env_line;
	char	*dollar_subline;
	char	*return_line;
	int		len_dollar_subline;
	int		i;
	int		j;
	int		k;
	int		z;
}				t_dollar;

typedef struct s_shell
{
	int			flag_for_el;
	int			flag_for_list;
	char		*tmp_str;
	char		*copy;
	char		*tmp;
	char		buff[9000];
	t_list_2l	*list;
	t_list_2l	*reserve_ptr;
}				t_shell;

typedef struct s_word_split
{
	t_list_2l	*list_for_args;
	t_list_2l	*node_for_args;
	char		*tmp;
	char		*buff;
	int			i;
	int			j;
}				t_word_split;

typedef struct s_ap
{
	int			words_counter;
	int			i;
	char		**args;
	t_list_2l	*tmp;
	t_list_2l	*list_for_args;
}				t_ap;

typedef struct s_parser
{
	t_com		*list_for_commands;
	t_com		*node_for_commands;
	char		*sub_line;
	int			numb_cmd;
	int			i;
	int			j;
}				t_parser;

t_list_2l	*ft_lstnew_2l(char *content, t_list_2l *back);
void		lister(t_shell *shell, t_list_2l *node);
t_list_2l	*ft_lstlast_2l(t_list_2l *lst);
void		ft_lstadd_back_2l(t_list_2l **lst, t_list_2l *new);
t_com		*ft_lstnew_sh(void);
void		ft_lstadd_back_sh(t_com **lst, t_com *new);
t_com		*ft_lstlast_sh(t_com *lst);
void		ft_enter(t_shell *shell, char ***envp, t_p *p,
				struct termios *term2);
int			ft_putchar(int c);
void		ft_up(t_shell *shell, t_p *p);
void		ft_down(t_shell *shell, t_p *p);
void		ft_delete(t_shell *shell);
void		ft_writer(t_shell *shell, t_p *p);
int			parser(char *line, char ***envp, t_p *p);
t_list_2l	*word_split(char *line);
char		*quote_word(char *line);
void		ft_buffjoin(char *s1, char *s2);
int			quote_value(char *quote_line, int ch);
void		parser_caller(char *input_line,
				char ***envp, t_p *p, struct termios *term2);
char		**my_realloc(char **a, int s);
int			redirect_estimator(t_list_2l *back);
void		printer(t_com *list_for_commands);
char		*dollar_estimator(char *line, char **envp);
void		ft_free_list(t_list_2l *l);
void		*allocator(t_p *p, void *a);
t_p			*ft_lstnew_p(void *content);
void		ft_lstadd_back_p(t_p **lst, t_p *new);
char		*redirect_changer(char *line);
int			is_in_single_quote(char *line, int index_dollar);
int			dollar_counter(char *line);
char		*dollar(char *line, char **envp);
int			is_env(char *new);
void		redirect_to_struct(t_com *list_for_commands,
				t_list_2l *list_for_args);
char		**arg_prepare(t_com *list_for_commands, char *line, char **envp);
int			dollar_counter(char *line);
int			is_env(char *new);
int			is_dollar(char *line, int i);
char		*dollar(char *line, char **envp);
void		ft_prompt(int std_out);
void		ft_setup_m(t_sh *m);
void		ft_cd(t_sh *m, char ***en);
size_t		ft_strcpy(char *dest, const char *src);
void		ft_env(char **envp);
void		ft_echo(t_sh *m);
void		ft_pwd(void);
void		ft_unset(t_sh *m, char ***en);
int			ft_check_unset(char *new, char **en);
void		ft_export(t_sh *m, char ***en);
int			ft_check_export(char *new, char **en);
char		**ft_export_add(char **en, char *new);
char		**ft_export_re(char **en, char *new, int i);
void		ft_export_print(char **en);
void		ft_exit(t_com *l, char **envp, t_p *p);
void		ft_free_t_com(t_com *l);
void		ft_free_t_sh(t_sh *m);
int			ft_count_array(char **split);
char		*ft_parser(char *buf, t_com **l);
void		ft_after_parsing(t_com **l, char ***envp, t_p *p, int *i);
void		ft_do_com(t_com *l, char ***envp, t_p *p);
void		ft_do_com_in_pipe(t_sh *m, char **envp);
int			ft_rec_com(t_sh *m);
void		ft_lstadd_back_com(t_com **lst, t_com *new);
t_com		*ft_lstnew_com(t_sh *content);
char		*ft_split_a(char *s, t_sh *m);
void		ft_join_text(t_sh *m, size_t i);
void		ft_exec(t_sh *m, char **envp);
void		ft_exec_2(t_sh *m, char **envp);
int			ft_search(t_sh *m, char **env);
int			ft_search_2(t_sh *m, char *pp, DIR *dirp, char *path);
int			*ft_pipe(t_com *l);
void		ft_pipe_2(t_com *l, char **envp);
void		ft_pipe_3(t_com *l, int	*fd);
void		ft_pipe_4(t_com *l, int *fd);
void		ft_fork(t_com *l, char **envp, int *fd);
void		ft_redirect(t_com *l);
void		ft_redirect_4(t_sh *m);
void		ft_first_cmd(t_com *l, int *fd);
void		ft_middle_cmd(t_com *l, int *fd);
void		ft_middle_2_cmd(t_com *l, int *fd);
void		ft_last_cmd(t_com *l, int *fd);
void		ft_last_2_cmd(t_com *l, int *fd);
void		ft_handler(int sig);
void		ft_do_and_free(t_com *l, char ***envp, t_p *p);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_copy_envp(char **envp);
int			ft_count_envp(char **envp);
char		*ft_getenv(char *name, char **en);
void		ft_swap_env(char **mas, int	i);
char		*ft_getenv_full(char *name, char **en);
int			ft_check_unset(char *new, char **en);
void		ft_free(char **arr, int index);
void		ft_free_array(char **arr);
int			ft_count_array(char **split);
void		ft_free_t_sh(t_sh *m);
void		ft_free_t_com(t_com *l);
void		ft_free_history(t_p *p);
char		**ft_free_array_return(char **envp, int index, char **ret);
void		ft_exit_child(t_sh *m, char **envp);
void		prs_init(t_parser *prs);
void		writter(char *str);
#endif
