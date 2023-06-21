/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:02:59 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/19 22:17:06 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_space_only(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = remove_quotes(str);
	while (new && new[i] == '\x07')
		i++;
	if (new && i > 0 && new[i] == 0)
		return (free(new), 1);
	return (free(new), 0);
}

char	*add_nonprintable(char *str)
{
	char	*output;
	int		i;

	i = 0;
	output = NULL;
	while (str && str[i])
	{
		if (ft_strchr(" \t", str[i]))
			output = join_to_str(output, '\x07');
		else
			output = join_to_str(output, str[i]);
		i++;
	}
	free (str);
	return (output);
}

static int	handle_nonprintable(char **output, char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\x01')
		*output = join_to_str(*output, str[i++]);
	return (i);
}

static int	handle_double_quotes(char **output, char *str)
{
	char	*quote;
	int		i;

	i = 0;
	quote = ft_strchr("\"'", str[i]);
	if (str[i + 1])
		i++;
	while (str[i] && quote[0] != str[i])
	{
		if (str[i] == '\x01')
		{
			i += handle_nonprintable(output, &str[i]);
			if (!str[i])
				break ;
		}
		else
			*output = join_to_str(*output, str[i++]);
	}
	return (i);
}

char	*filter_expanded(char *str, int i)
{
	char	*output;

	output = NULL;
	while (str && str[++i])
	{
		while (str[i] && !ft_strchr("\"'", str[i]) && str[i] != '\x01')
			output = join_to_str(output, str[i++]);
		if (str[i] && str[i] == '\x01')
		{
			if (str[i + 1] && !ft_strchr(&str[i + 1], '\x01'))
				continue ;
			i += handle_nonprintable(&output, &str[i]);
		}
		else if (str[i])
			i += handle_double_quotes(&output, &str[i]);
		if (!str[i])
			break ;
	}
	return (output);
}
