/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils_define2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:03:26 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/17 17:45:01 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmd_to_list(t_cmdshell **lst, t_cmds *cmds)
{
	t_cmdshell	*new;
	t_cmdshell	*tmp;

	if (!cmds)
		return ;
	new = malloc(sizeof(t_tokens));
	if (!new)
		return ;
	new->cmds = cmds;
	new->next = NULL;
	new->prev = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	init_struct_cmds(t_cmds **cmds)
{
	(*cmds)->redis = NULL;
	(*cmds)->args = NULL;
	(*cmds)->subshell = NULL;
	(*cmds)->operator = -1;
	return (0);
}
