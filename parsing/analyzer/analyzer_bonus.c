/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:36:28 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/12 21:32:31 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*join_with_space(char *old, char *arg)
{
	char	*output;
	int		i;
	int		j;

	output = malloc(ft_strlen(old) + ft_strlen(arg) + 2);
	if (!output)
		print_error(NULL, NULL, 1);
	i = 0;
	j = 0;
	while (old && old[j])
		output[i++] = old[j++];
	if (old)
		output[i++] = ' ';
	j = 0;
	while (arg && arg[j])
		output[i++] = arg[j++];
	output[i] = '\0';
	if (old)
		free(old);
	return (output);
}

char	*handle_subshell(t_tokens **tmp)
{
	char	*output;
	int		par;

	output = NULL;
	par = 0;
	while ((*tmp))
	{
		if (!ft_strcmp((*tmp)->str, "("))
			output = ((par++), ft_strjoin(output, (*tmp)->str));
		else if (!ft_strcmp((*tmp)->str, ")"))
			output = ((par--), ft_strjoin(output, (*tmp)->str));
		else if ((*tmp)->prev->str && !ft_strcmp((*tmp)->prev->str, "("))
			output = ft_strjoin(output, (*tmp)->str);
		else
			output = join_with_space(output, (*tmp)->str);
		if (par == 0)
			break ;
		(*tmp) = (*tmp)->next;
	}
	return (output);
}
