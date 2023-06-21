/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 07:50:54 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 13:24:01 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skipp_dollar(t_tokens **tmp, int *count_dollar, char **output)
{
	t_tokens	*tmp2;
	t_tokens	*tmp3;

	tmp3 = NULL;
	if ((*tmp)->prev)
		tmp3 = (*tmp)->prev;
	while ((*tmp) && !ft_strcmp((*tmp)->str, "$"))
	{
		(*count_dollar)++;
		tmp2 = (*tmp);
		(*tmp) = (*tmp)->next;
	}
	if (!(*tmp))
	{
		if ((*count_dollar) % 2 != 0 && !ft_strcmp(tmp2->str, "$"))
			(*output) = ft_strjoin((*output), tmp2->str);
		return (1);
	}
	if ((*tmp) && !ft_strcmp((*tmp)->str, "\"") && \
		tmp3 && !ft_strcmp(tmp3->str, "\""))
		if ((*count_dollar) % 2 != 0 && !ft_strcmp(tmp2->str, "$"))
			(*output) = ft_strjoin((*output), tmp2->str);
	return (0);
}

t_tokens	*expantion_tokenizer(char *token)
{
	t_tokens	*tokens;
	char		**output;
	char		*to_split;
	int			i;

	to_split = ((i = 0), NULL);
	while (token && token[i])
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
		{
			to_split = join_to_str(to_split, '\x07');
			to_split = join_to_str(to_split, token[i]);
			to_split = join_to_str(to_split, '\x07');
		}
		else
			to_split = join_to_str(to_split, token[i]);
		i++;
	}
	i = 0;
	tokens = NULL;
	output = ft_split(to_split, '\x07');
	while (output && output[i])
		create_tokens(&tokens, ft_strdup(output[i++]));
	return (free(to_split), free_double_ptr(output), tokens);
}

int	count_split(char **split)
{
	int	count;

	count = 0;
	while (split && split[count])
		count++;
	return (count);
}

t_tokens	*expention_wildcard_case(char *to_handle)
{
	t_tokens	*tokens;

	tokens = NULL;
	if (!ft_strchr(to_handle, '\x02'))
		return (wildcard(to_handle));
	create_tokens(&tokens, remove_nonprint(ft_strdup(to_handle), "\x02"));
	return (tokens);
}
