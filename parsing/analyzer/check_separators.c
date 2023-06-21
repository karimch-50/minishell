/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:29:32 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/17 17:41:49 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_redirections(t_syntax_check check)
{
	if (check.sp_id < 4)
	{
		if (!check.token->next)
		{
			here_doc_befor_error(check.all_tokens, check.index);
			return (syntx_error("newline"), 1);
		}
		check.sp_id = is_separator(check.token->next->str, check.sep);
		if (check.sp_id != -1)
		{
			syntx_error(check.sep[check.sp_id]);
			here_doc_befor_error(check.all_tokens, check.index);
			return (1);
		}
	}
	return (0);
}

int	check_operators(t_syntax_check check)
{
	if (check.sp_id > 3 && check.sp_id < 7)
	{
		if (!check.token->prev)
			return (syntx_error(check.sep[check.sp_id]), 1);
		if (!check.token->next)
		{
			here_doc_befor_error(check.all_tokens, check.index);
			return (syntx_error("newline"), 1);
		}
		check.sp_id = is_separator(check.token->next->str, check.sep);
		if (check.sp_id != -1 && check.sp_id > 3 && \
		check.sp_id != 8 && check.sp_id != 7)
		{
			syntx_error(check.sep[check.sp_id]);
			here_doc_befor_error(check.all_tokens, check.index);
			return (1);
		}
	}
	return (0);
}
