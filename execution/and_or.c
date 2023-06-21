/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:02:43 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/17 17:59:55 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_or(t_cmdshell *cmds)
{
	t_cmdshell	*tmp_cmds;
	int			count;

	tmp_cmds = cmds;
	count = 0;
	while (tmp_cmds)
	{
		if (tmp_cmds->cmds->operator == OR)
			count++;
		tmp_cmds = tmp_cmds->next;
	}
	return (count);
}

int	count_and(t_cmdshell *cmds)
{
	t_cmdshell	*tmp_cmds;
	int			count;

	tmp_cmds = cmds;
	count = 0;
	while (tmp_cmds)
	{
		if (tmp_cmds->cmds->operator == AND)
			count++;
		tmp_cmds = tmp_cmds->next;
	}
	return (count);
}

int	and(t_global *global, t_cmdshell **all_cmds, int cou_or)
{
	if (global->exit_status == 0 && (*all_cmds) && \
	(*all_cmds)->prev->cmds->operator == AND)
		return (2);
	else if (global->exit_status != 0 && \
		(*all_cmds)->prev->cmds->operator == AND)
	{
		if (cou_or != 0)
		{
			while (*all_cmds && (*all_cmds)->cmds->operator != OR)
				(*all_cmds) = (*all_cmds)->next;
			if (*all_cmds)
				(*all_cmds) = (*all_cmds)->next;
			return (2);
		}
		return (1);
	}
	return (-1);
}

int	or(t_global *global, t_cmdshell **all_cmds, int cou_and)
{
	if (global->exit_status != 0 && (*all_cmds) && \
	(*all_cmds)->prev->cmds->operator == OR)
		return (2);
	else if (global->exit_status == 0 && \
		(*all_cmds)->prev->cmds->operator == OR)
	{
		if (cou_and != 0)
		{
			while (*all_cmds && (*all_cmds)->cmds->operator != AND)
				(*all_cmds) = (*all_cmds)->next;
			if (*all_cmds)
				(*all_cmds) = (*all_cmds)->next;
			return (2);
		}
		return (1);
	}
	return (-1);
}
