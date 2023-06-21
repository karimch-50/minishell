# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:39:56 by kchaouki          #+#    #+#              #
#    Updated: 2023/06/21 13:15:22 by kchaouki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAME_B = minishell_bonus

LIBFT = libft/libft.a

PARSING = parsing/parser.c \
		  parsing/analyzer/syntax_error.c \
		  parsing/analyzer/here_doc_error_case.c \
		  parsing/analyzer/check_separators.c \
		  parsing/create_tokens.c \
		  parsing/global_split_utils.c \
		  parsing/global_split.c \
		  parsing/shared_utils_define.c \
		  parsing/shared_utils_define2.c \
		  minishell_utils.c \
		  parsing/here_doc.c \
		  all_free.c \
		  all_free2.c

EXECUTION = execution/expention/expantion_utils.c \
		  	execution/expention/expantion_utils2.c \
		  	execution/expention/expantion_utils3.c \
		  	execution/expention/expantion_utils4.c \
			execution/expention/expantion_utils5.c \
			execution/builtins/environment.c \
			execution/builtins/export.c \
			execution/builtins/export2.c \
			execution/builtins/unset.c \
			execution/builtins/exit.c \
			execution/builtins/pwd.c \
			execution/builtins/cd.c \
			execution/builtins/echo.c \
			execution/redirections.c \
			execution/manage_redirections.c \
			execution/exec_commands.c \
			execution/extract_path.c \
			execution/get_env.c \
			execution/prepare_command.c \
			execution/pipe.c \
			execution/check_builtin.c \
			execution/exec_cmd.c \
			execution/subshell.c \
			execution/and_or.c \
			execution/wildcard.c

SRCS_M = minishell.c $(PARSING) \
		 parsing/define_mandatory.c \
		 parsing/synt_error_mandatory.c \
		 execution/expention/args_expantion.c \
		 execution/expention/redis_expantion.c \
		 $(EXECUTION)

SRCS_B = minishell.c $(PARSING) \
		 parsing/define_bonus.c \
		 parsing/synt_error_bonus.c \
		 parsing/analyzer/analyzer_bonus.c \
		 execution/expention/args_expantion_bonus.c \
		 execution/expention/redis_expantion_bonus.c \
		 $(EXECUTION)

OBJS_M = $(SRCS_M:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

RDL = -lreadline \
	-L/goinfre/kchaouki/brew/opt/readline/lib

FLAGS = -Wall -Wextra -Werror

CCe = cc

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft && make clean -C libft

%.o : %.c
	$(CCe) $(FLAGS) -I/goinfre/kchaouki/brew/opt/readline/include -c $< -o $@

$(NAME): $(OBJS_M) minishell.h
	$(CCe) $(FLAGS) $(OBJS_M) $(RDL) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(NAME_B)

$(NAME_B) : $(OBJS_B) minishell.h
	$(CCe) $(FLAGS) $(OBJS_B) $(RDL) $(LIBFT) -o $(NAME_B)

clean:
	rm -rf $(OBJS_M) $(OBJS_B)

fclean: clean 
	rm -rf $(NAME) $(NAME_B) $(LIBFT) && make clean -C libft

re : fclean all

.PHONY: all clean fclean re bonus
