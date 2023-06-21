/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:35:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 13:10:33 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expanded_into_heredoc(char *token, t_global *global)
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
			output = expantion_dollar_case(global, &tmp, output, 1);
			if (!tmp)
				break ;
		}
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	free_tokens(tokens);
	return (output);
}

static void	herdoc_expander(t_global *global, char *line, char *delem, int fd)
{
	char	*output;

	output = NULL;
	if (ft_strchr(delem, '"') || ft_strchr(delem, '\''))
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		output = expanded_into_heredoc(line, global);
		ft_putstr_fd(output, fd);
		ft_putstr_fd("\n", fd);
	}
	free(output);
}

static int	here_doc(t_global *global, char *delimiter)
{
	char	*line;
	int		fd[2];
	int		read_fd;
	char	*delem;

	if (pipe(fd) == -1)
		return (print_error(NULL, NULL, -1), -1);
	read_fd = dup(fd[0]);
	if (close (fd[0]) == -1)
		return (print_error(NULL, NULL, -1), -1);
	delem = remove_quotes(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (free(delem), -3);
		if (ft_strcmp(line, delem) == 0)
			break ;
		herdoc_expander(global, line, delimiter, fd[1]);
		free(line);
	}
	if (close (fd[1]) == -1)
		return (print_error(NULL, NULL, -1), -1);
	return (free(delem), free(line), read_fd);
}

static int	get_last_heredoc(t_global *global, t_redis *redis)
{
	t_redis	*tmp;
	int		fd_new;
	int		fd_prev;

	fd_new = -2;
	fd_prev = -1;
	tmp = redis;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (fd_prev != -1 && close (fd_prev) == -1)
				return (print_error(NULL, NULL, -1), -1);
			fd_new = here_doc(global, tmp->str);
			fd_prev = fd_new;
			if (fd_new == -3)
				return (-3);
			if (fd_new == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (fd_new);
}

int	run_heredocs(t_global *global)
{
	t_cmdshell	*tmp;

	tmp = global->all_commands;
	while (tmp)
	{
		tmp->cmds->fd_herdoc = get_last_heredoc(global, tmp->cmds->redis);
		if (tmp->cmds->fd_herdoc == -3)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
