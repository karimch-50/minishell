/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:36:25 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/18 15:13:30 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->var);
		free (tmp->value);
		free (tmp);
		tmp = tmp2;
	}
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = tokens;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = tmp2;
	}
}

void	free_token_utils(t_utils *utils, t_tokens *tokens)
{
	free_tokens(tokens);
	free_double_ptr(utils->spl_redi);
	free_double_ptr(utils->spl_sp_char);
	free(utils);
}
