/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:07:55 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 19:27:23 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*remove_nonprint(char *str, char *charset)
{
	char	*output;
	int		i;

	i = 0;
	output = NULL;
	while (str && str[i])
	{
		if (str[i] != is_in_charset(str[i], charset))
			output = join_to_str(output, str[i]);
		i++;
	}
	free(str);
	return (output);
}

int	expanded_into_redis(t_global *global, t_redis **redis, t_redis *old_redis)
{
	t_tokens	*tokens;
	t_tokens	*tmp;
	char		*output;

	tokens = expantion_tokenizer(old_redis->str);
	output = ((tmp = tokens), NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->str, "$"))
		{
			output = expantion_dollar_case(global, &tmp, output, 1);
			if (!tmp)
				break ;
		}
		else if (!ft_strcmp(tmp->str, "'") || !ft_strcmp(tmp->str, "\""))
			output = expantion_quote_case(global, &tmp, output, 0);
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	if (add_expanded_to_redis(redis, output, old_redis->str, old_redis->type))
		return (free_tokens(tokens), free(output), 1);
	return (free_tokens(tokens), free(output), 0);
}

static void	sequel(t_global *global, t_tokens **tmp, char **output)
{
	*output = join_to_str(*output, '\x01');
	*output = expantion_dollar_case(global, tmp, *output, 1);
	*output = join_to_str(*output, '\x01');
}

void	expanded_into_args(t_args **args, char *token, t_global *global)
{
	t_tokens	*tokens;
	t_tokens	*tmp;
	char		*output;

	tokens = expantion_tokenizer(token);
	output = ((tmp = tokens), NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->str, "$"))
		{
			sequel(global, &tmp, &output);
			if (!tmp)
				break ;
		}
		else if (!ft_strcmp(tmp->str, "'") || !ft_strcmp(tmp->str, "\""))
			output = expantion_quote_case(global, &tmp, output, 0);
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	free_tokens(tokens);
	add_expanded_to_args(args, output);
	free(output);
}
