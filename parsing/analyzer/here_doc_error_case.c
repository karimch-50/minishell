/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_error_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:21:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/17 17:40:37 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	here_doc_error_case(char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		free(line);
	}
	free(line);
}

static void	run_here_docs(t_tokens	*here_docs)
{
	t_tokens	*tmp;

	if (here_docs)
	{
		tmp = here_docs;
		while (tmp)
		{
			here_doc_error_case(tmp->str);
			tmp = tmp->next;
		}
	}
	free_tokens(here_docs);
}

void	here_doc_befor_error(t_tokens *tokens, int index)
{
	t_tokens	*here_docs;
	t_tokens	*tmp;
	int			j;

	tmp = tokens;
	if (index == count_tokens(tokens))
		return ;
	here_docs = ((j = 0), NULL);
	while (tmp && j < index)
	{
		if (tmp && ft_strnstr(tmp->str, "<<", 2))
		{
			tmp = tmp->next;
			j++;
			create_tokens(&here_docs, ft_strdup(tmp->str));
		}
		j++;
		tmp = tmp->next;
	}
	run_here_docs(here_docs);
}
