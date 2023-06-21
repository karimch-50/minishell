/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:32:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 16:55:48 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*delete_node(t_env **env_exp, char *var)
{
	t_env	*tmp_env_exp;

	tmp_env_exp = *env_exp;
	while (tmp_env_exp)
	{
		if (ft_strcmp(var, tmp_env_exp->var) == 0)
			return (tmp_env_exp);
		tmp_env_exp = tmp_env_exp->next;
	}
	return (NULL);
}

void	unset_var(t_env **env_exp, char *var)
{
	t_env	*del_node;

	del_node = delete_node(env_exp, var);
	if (!del_node)
		return ;
	if (del_node == *env_exp)
		*env_exp = del_node->next;
	if (del_node->next)
		del_node->next->prev = del_node->prev;
	if (del_node->prev)
		del_node->prev->next = del_node->next;
	free(del_node->value);
	free(del_node->var);
	free(del_node);
}

void	call_unset(t_env **env, t_env **export, char *str)
{
	unset_var(export, str);
	unset_var(env, str);
}

void	unset(t_global *global, t_env **env, t_env **export, t_args *args)
{
	t_args	*tmp_args;

	tmp_args = args;
	global->exit_status = 0;
	if (tmp_args && tmp_args->next)
	{
		while (tmp_args)
		{
			if (identifier(tmp_args->str, "unset") == 1)
			{
				if (tmp_args->str[0] == '#')
				{
					global->exit_status = 0;
					break ;
				}
				tmp_args = tmp_args->next;
				global->exit_status = 1;
				continue ;
			}
			call_unset(env, export, tmp_args->str);
			tmp_args = tmp_args->next;
		}
	}
}
