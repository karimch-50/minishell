/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 16:37:11 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/parsing.h"
# include "execution/execution.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <dirent.h>
# include <sys/stat.h>

# define EIAD ": is a directory\n"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"
# define ESYNTX "minishell: syntax error near unexpected token `"
# define EAMBGRD ": ambiguous redirect\n"

typedef enum e_redirtypes
{
	FILE_APPEND,
	HEREDOC,
	FILE_IN,
	FILE_OUT,
	OR,
	AND,
	PIPE
}	t_rtype;

typedef struct s_global
{
	int			exit_status;
	pid_t		*pid;
	int			pipe[2];
	int			prev_fd;
	t_env		*env;
	t_env		*export;
	t_cmdshell	*all_commands;
}			t_global;

int			init_global(t_global **global, char **env);
int			fill_global_struct(t_global **global, char *line);
int			run_heredocs(t_global *global);
/*------- all free --------*/
void		free_double_ptr(char **str);
void		free_commands(t_cmdshell *comands);
void		global_free(t_global *global);
void		free_redis(t_redis *redis);
void		free_args(t_args *args);
void		free_env(t_env *env);
void		free_tokens(t_tokens *tokens);
void		free_token_utils(t_utils *utils, t_tokens *tokens);

/*========== builtins ==============*/
void		exitt(t_global *global, t_args *args);
void		pwd(t_global *global);
void		cd(t_global *global, t_args	*args, t_env *export);
void		echo(t_global *global, t_args *args);
/*--------- unset ------------------*/
void		unset(t_global *global, t_env **env, t_env **export, t_args *args);
int			identifier(char *str, char *exp_uns);
/*------------- enviroment -------------*/
void		add_to_env(t_env **env, char *var, char *value);
size_t		find_equale(char *str);
void		print_env(t_global *global);
/*----------- export -------------------*/
t_env		*_export(t_env *env);
void		print_export(t_env *export);
int			search_var(t_env *export, char *var);
void		edit_value(t_env *env, t_env *export, char *str);
void		edit_value2(t_env *exp_or_env, char *var, size_t equal, char *str);
void		add_to_export_or_print(t_global *global, t_env **env, \
			t_env **export, t_args *args);
void		print_value(char *str);
/*========== end builtins ==============*/

/*=========== execution ================*/
void		execution(t_global *global);
t_recipe	prepare_command(t_global *global, t_cmdshell *all_cmds);
void		sig_handl(int sig);
void		builtins(t_global *global, t_cmdshell *all_cmds);
void		not_builtin(t_global *global, t_cmdshell *all_cmds, \
			int i, int count);
void		run_subshell(t_global *global, t_cmdshell *cmd, int i, int count);
void		alloc_pid(t_global *global, t_cmdshell *all_cmds, int count);
int			is_builtin(char *token);

/*-------- and or ----------*/
int			or(t_global *global, t_cmdshell **all_cmds, int cou_and);
int			and(t_global *global, t_cmdshell **all_cmds, int cou_or);
int			count_and(t_cmdshell *cmds);
int			count_or(t_cmdshell *cmds);

/*---------- pipe --------------*/
void		create_pipe(t_global *global);
void		close_pipe(t_global *global, int count, int i);
void		read_write_pipe(t_global *global, t_cmdshell *cmd, \
			int i, int count);

/*----------- args expand ---------*/
t_args		*args_expander(t_global *global, t_args	*args);
void		expanded_into_args(t_args **args, char *token, t_global *global);
char		*expantion_dollar_case(t_global *global, t_tokens **tmp, \
			char *old, int flag);
char		*expantion_quote_case(t_global *global, t_tokens **tmp, \
			char *old, int flag);
int			expanded_into_redis(t_global *global, t_redis **redis, \
			t_redis *old_redis);

/*----------- redis expand ---------*/
t_redis		*redis_expander(t_global *global, t_redis *redis);
int			manage_redirection(t_global *global, t_redis *redis);
int			open_redis(t_global *global, t_redis *redis, \
			int *fd_read, int *fd_write);
int			manage_redirection_builtins(t_global *global, t_cmdshell *cmd);
/*=========== end execution ==============*/

void		print_error(char *msg, char *arg, int status);
#endif