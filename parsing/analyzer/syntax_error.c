/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 08:56:35 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 13:19:05 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	syntx_error(char *arg)
{
	ft_putstr_fd(ESYNTX, 2);
	if (arg[0] == '\"' || arg[0] == '\"')
		ft_putchar_fd(*arg, 2);
	else
		ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'\n", 2);
}

int	is_separator(char *token, char **sep)
{
	int	i;

	i = -1;
	while (sep && sep[++i])
	{
		if (ft_strnstr(token, sep[i], ft_strlen(sep[i])))
			return (i);
	}
	return (-1);
}

static int	check_quotes(char *token)
{
	char	*quote;
	int		i;

	i = -1;
	quote = NULL;
	while (token && token[++i])
	{
		while (token[i] && !ft_strchr("\"'", token[i]))
			i++;
		if (!token[i])
			break ;
		quote = ft_strchr("\"'", token[i]);
		if (!token[i + 1] && quote[0])
			return (syntx_error(&quote[0]), 1);
		else if (token[i + 1])
			i++;
		while (token[i] && quote[0] != token[i])
			i++;
		if (!token[i] && quote[0] != token[i])
			return (syntx_error(&quote[0]), 1);
	}
	return (0);
}

int	syntax_error_handler(t_tokens *tokens)
{
	t_syntax_check	check;
	t_tokens		*tmp;

	tmp = tokens;
	check = fill_syntax_check(tokens, tmp);
	if (!check.sep)
		print_error(NULL, NULL, 1);
	while (tmp)
	{
		if (check_quotes(tmp->str))
			return (here_doc_befor_error(tokens, check.index), \
			free_double_ptr(check.sep), 258);
		check.sp_id = is_separator(tmp->str, check.sep);
		check.token = tmp;
		if (check_separators(check, &check.par, &check.index_par))
			return (free_double_ptr(check.sep), 258);
		check.index++;
		tmp = tmp->next;
	}
	if (check.par > 0)
		return (free_double_ptr(check.sep), \
		here_doc_befor_error(check.all_tokens, check.index_par), \
		syntx_error("("), 258);
	return (free_double_ptr(check.sep), 0);
}
