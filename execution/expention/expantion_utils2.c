/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:30:45 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/19 22:41:24 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value(char *to_expand, t_env *env)
{
	char	*output;
	t_env	*tmp;

	output = NULL;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, to_expand))
		{
			output = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (output);
}

char	*remove_quotes(char *str)
{
	char	*output;
	char	*quote;
	int		i;

	i = -1;
	quote = NULL;
	output = NULL;
	while (str && str[++i])
	{
		while (str[i] && !ft_strchr("\"'", str[i]))
			output = join_to_str(output, str[i++]);
		if (!str[i])
			break ;
		quote = ft_strchr("\"'", str[i]);
		if (str[i + 1])
			i++;
		while (str[i] && quote[0] != str[i])
			output = join_to_str(output, str[i++]);
	}
	if (!output)
		return (ft_strdup(""));
	return (output);
}

char	**prepare_to_fill(t_redis **redis, int type, char *expended)
{
	char		**split;
	char		*new_expended;

	split = NULL;
	new_expended = filter_expanded(expended, -1);
	new_expended = remove_nonprint(new_expended, "\x01");
	if (new_expended)
		split = ft_split(new_expended, '\x07');
	else
		fill_list_redis(redis, ft_strdup(""), type);
	return (free(new_expended), split);
}

char	*handle_non_alnum(char	*output, t_tokens **tmp, int exit_status)
{
	char	*status;

	if ((*tmp) && (!ft_strcmp((*tmp)->str, "\"") \
	|| !ft_strcmp((*tmp)->str, "'")))
		(*tmp) = (*tmp)->prev;
	else if ((*tmp) && !ft_strcmp((*tmp)->str, "?"))
	{
		status = ft_itoa(exit_status);
		output = ft_strjoin(output, status);
		free (status);
	}
	else if ((*tmp) && !ft_strcmp((*tmp)->str, "@"))
		return (output);
	else
	{
		output = ft_strjoin(output, (*tmp)->prev->str);
		output = ft_strjoin(output, (*tmp)->str);
	}
	return (output);
}

char	*handle_alnum(t_env *env, char *output, char *str, int flag)
{
	char	*value;

	if (ft_isdigit(str[0]))
			output = ft_strjoin(output, &str[1]);
	else
	{
		value = get_value(str, env);
		if (!value)
			return (NULL);
		if (flag)
			value = add_nonprintable(value);
		output = ft_strjoin(output, value);
		free(value);
	}
	return (output);
}
