/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:02 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/14 13:36:07 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free (str[i++]);
	free(str);
}

void	free_commands(t_cmdshell *comands)
{
	t_cmdshell	*tmp;

	while (comands)
	{
		tmp = comands;
		free_redis(comands->cmds->redis);
		free_args(comands->cmds->args);
		free(comands->cmds->subshell);
		free(comands->cmds);
		comands = comands->next;
		free(tmp);
	}
}

void	global_free(t_global *global)
{
	free_env(global->env);
	free_env(global->export);
	free(global);
}

void	free_redis(t_redis *redis)
{
	t_redis	*tmp;
	t_redis	*tmp2;

	tmp = redis;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}

void	free_args(t_args *args)
{
	t_args	*tmp;
	t_args	*tmp2;

	tmp = args;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}
