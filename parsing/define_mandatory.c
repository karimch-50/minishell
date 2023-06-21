/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:31 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/18 16:09:35 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_struct_utils(t_utils **utils)
{
	*utils = malloc(sizeof(t_utils));
	if (!(*utils))
		return (-1);
	(*utils)->spl_redi = ft_split(">> << < >", ' ');
	if (!((*utils)->spl_redi))
		return (-1);
	(*utils)->spl_sp_char = ft_split("|", ' ');
	if (!((*utils)->spl_sp_char))
		return (-1);
	(*utils)->sp_id = -1;
	(*utils)->red_id = -1;
	(*utils)->red_id_prev = -1;
	(*utils)->sp_id_prev = -1;
	(*utils)->red_id_prev_prev = -1;
	return (0);
}

void	check_define(t_cmds *cmds, t_tokens *tokens, t_utils *utils)
{
	if (tokens->prev == NULL || utils->sp_id_prev != -1)
		check_node1(&cmds, tokens, utils);
	else if (utils->red_id != -1)
	{
		if (tokens->next)
			fill_list_redis(&cmds->redis, \
				ft_strdup(tokens->next->str), utils->red_id);
		utils->red_id = -1;
	}
	else if (utils->red_id_prev_prev != -1 && utils->red_id == -1 \
		&& utils->sp_id == -1 && cmds->args == NULL)
		fill_list_args(&cmds->args, ft_strdup(tokens->str));
	else if (tokens->prev != NULL && utils->red_id_prev == -1 \
		&& utils->sp_id == -1 && utils->sp_id_prev == -1)
		fill_list_args(&cmds->args, ft_strdup(tokens->str));
}

t_tokens	*fill_struct_cmds(t_cmds *cmds, t_tokens *tokens, t_utils *utils)
{
	int	i;

	i = 0;
	while (tokens && utils->sp_id == -1)
	{
		utils->red_id = find_separator(utils->spl_redi, tokens->str);
		utils->sp_id = find_separator(utils->spl_sp_char, tokens->str);
		if (utils->sp_id != -1)
			utils->sp_id += 6;
		if (tokens->prev)
		{
			utils->red_id_prev = find_separator(utils->spl_redi, \
				tokens->prev->str);
			utils->sp_id_prev = find_separator(utils->spl_sp_char, \
				tokens->prev->str);
		}
		if (i++ >= 2)
			utils->red_id_prev_prev = find_separator(utils->spl_redi, \
				tokens->prev->prev->str);
		check_define(cmds, tokens, utils);
		cmds->operator = utils->sp_id;
		tokens = tokens->next;
	}
	return (tokens);
}

t_tokens	*analyzer(t_tokens *tokens, int	*exit_status)
{
	int	status;

	status = syntax_error_handler(tokens);
	if (status == 258)
	{
		*exit_status = status;
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
