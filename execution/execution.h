/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:09:19 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 13:23:21 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_vars
{
	int		i;
	int		j;
	int		last_s;
	int		last_p;
}	t_vars;

typedef struct s_recipe
{
	char	*command;
	char	**args;
	char	**envp;
}	t_recipe;

char		*valid_command_path(char **paths, char *cmd);
char		**get_paths(t_env *env);
char		**get_env(t_env *env);

int			input_redirection(char *infile);
int			output_redirection(char *outfile);
int			append_output(char *outfile);

/*========= start expender =============*/
char		*remove_quotes(char *str);
t_tokens	*expantion_tokenizer(char *token);
char		*get_value(char *to_expand, t_env *env);
void		add_expanded_to_args(t_args **args, char *expended);
int			add_expanded_to_redis(t_redis **redis, char *expended, \
			char *token, int type);
char		*handle_non_alnum(char	*output, t_tokens **tmp, int exit_status);
char		*handle_alnum(t_env *env, char *output, char *str, int flag);
int			skipp_dollar(t_tokens **tmp, int *count_dollar, char **output);
t_tokens	*expention_wildcard_case(char *to_handle);
char		**split_expended(char *token);
int			count_split(char **split);
char		*filter_expanded(char *str, int i);
char		**prepare_to_fill(t_redis **redis, int type, char *expended);
int			has_space_only(char *str);
char		*remove_nonprint(char *str, char *charset);
char		*add_nonprintable(char *str);
t_tokens	*wildcard(char	*arg);
/*========= end expender =============*/

#endif