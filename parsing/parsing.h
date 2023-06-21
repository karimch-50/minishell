/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:09:38 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 13:24:48 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <signal.h>

/*--------------tokens's linked list-------------*/
typedef struct s_tokens
{
	char			*str;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

/*----------------check syntax error-------------*/
typedef struct s_syntax_check
{
	t_tokens	*all_tokens;
	t_tokens	*token;
	char		**sep;
	int			index_par;
	int			par;
	int			index;
	int			sp_id;
}	t_syntax_check;

/*-------------check for global split------------*/
typedef struct s_check
{
	char	*str;
	char	*ot;
	char	**split;
	int		dq;
	int		sq;
	int		sid;
}			t_check;

/*------linked list of environment variables------*/
typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}			t_env;

/*---------linked list for redirections--------*/
typedef struct s_redis
{
	char			*str;
	int				need_expand;
	int				type;
	struct s_redis	*next;
}		t_redis;

/*----------linked list for arguments----------*/
typedef struct s_args
{
	char			*str;
	struct s_args	*next;
}		t_args;

/*-------utils to fill commands's struct------*/
typedef struct s_utils
{
	char	**spl_sp_char;
	char	**spl_redi;
	int		red_id;
	int		sp_id;
	int		red_id_prev;
	int		sp_id_prev;
	int		red_id_prev_prev;
}			t_utils;

/*-------------command's struct---------------*/
typedef struct s_cmds
{
	t_redis	*redis;
	t_args	*args;
	int		fd_herdoc;
	int		operator;
	char	*subshell;
}				t_cmds;

/*----------linked list of commands--------*/
typedef struct s_cmdshell
{
	t_cmds				*cmds;
	struct s_cmdshell	*next;
	struct s_cmdshell	*prev;
}	t_cmdshell;

/*========= start token =============*/
int				split_and_fill_list(char *output, t_tokens **tokens);
int				init_check(t_check	*check, char *read_line);
int				find_separator(char **sep, char *str);
char			*join_to_str(char *str, char c);
void			create_tokens(t_tokens **lst, char *str);
void			dq_sq(t_check *check, int *i, int *dq_or_sq);
/*========= end token =============*/

/*========= start analyzer =============*/
t_tokens		*analyzer(t_tokens *tokens, int	*exit_status);
int				syntax_error_handler(t_tokens *tokens);
t_syntax_check	fill_syntax_check(t_tokens *all_tokens, t_tokens *token);
void			print_error(char *msg, char *arg, int status);
void			here_doc_befor_error(t_tokens *tokens, int index);
int				is_separator(char *token, char **sep);
int				check_separators(t_syntax_check	check, int *par, int *i_par);
int				count_tokens(t_tokens *tokens);
void			syntx_error(char *arg);
int				check_redirections(t_syntax_check check);
int				check_operators(t_syntax_check check);
char			*handle_subshell(t_tokens **tmp);
/*========= end analyzer =============*/

/*========= start parser =============*/
int				init_struct_utils(t_utils **utils);
int				init_struct_cmds(t_cmds **cmds);
int				find_separator(char **sep, char *str);
void			add_cmd_to_list(t_cmdshell **lst, t_cmds *cmds);
t_env			*create_env(char **envp);
void			check_node1(t_cmds **cmd, t_tokens *tmp, t_utils *utils);
void			fill_list_redis(t_redis **lst, char *str, int type);
void			fill_list_args(t_args **lst, char *str);
t_tokens		*fill_struct_cmds(t_cmds *cmds, \
				t_tokens *tokens, t_utils *utils);
/*========= end parser =============*/

#endif