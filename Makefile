NAME		= minishell

SRCS	=	./srcs/minishell.c \
			./srcs/list_func.c \
			./srcs/history.c \
			./srcs/parser.c \
			./srcs/word_instance.c \
			./srcs/list_sh_func.c \
			./srcs/parser_tools.c \
			./srcs/dollar.c \
			./srcs/line_corrector.c \
			./srcs/word_instance_2.c \
			./srcs/redirect_parse.c \
			./srcs/arg_prepare.c \
			./srcs/dollar_tools.c \
			./srcs/ft_cd.c \
			./srcs/ft_echo.c \
			./srcs/ft_env.c \
			./srcs/ft_envp_utils.c \
			./srcs/ft_exec.c \
			./srcs/ft_exit.c \
			./srcs/ft_export_2.c \
			./srcs/ft_export.c \
			./srcs/ft_free.c \
			./srcs/ft_lists_of_command.c \
			./srcs/ft_parser.c \
			./srcs/ft_pipe.c \
			./srcs/ft_pipe_2.c \
			./srcs/ft_pipe_3.c \
			./srcs/ft_pwd.c \
			./srcs/ft_redirect.c \
			./srcs/ft_search.c \
			./srcs/ft_unset.c \
			./srcs/ft_unset_2.c \
			./srcs/main_obellado.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc	-Wall -Werror -Wextra

RM				= rm -f

LIBS			= libft/libft.a -ltermcap -fsanitize=address

LIB				= libft/libft.a

NAME			= minishell

all:			$(NAME)


$(NAME):		$(LIB) $(OBJS)
				$(CC) -o ${NAME} ${OBJS} ${LIBS}

$(LIB):
		make -C libft

%.o:	%.c Makefile minishell.h
		$(CC) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
