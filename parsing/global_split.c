/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:09:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 13:13:45 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_quote(t_check *check, int *i)
{
	if (check->str[*i] == '"' && check->sq == 0 && check->dq == 0)
		dq_sq(check, i, &check->dq);
	else if (check->str[*i] == '\'' && check->sq == 0 && check->dq == 0)
		dq_sq(check, i, &check->sq);
	else if (check->str[*i] == '"' && check->sq == 0 && check->dq == 1)
	{
		check->dq = 0;
		check->ot = join_to_str(check->ot, check->str[*i]);
	}
	else if (check->str[*i] == '\'' && check->sq == 1 && check->dq == 0)
	{
		check->sq = 0;
		check->ot = join_to_str(check->ot, check->str[*i]);
	}
	else
		check->ot = join_to_str(check->ot, check->str[*i]);
}

static void	check_space_tab(t_check *check, int *i)
{
	while (check->str[*i] && (check->str[*i] == ' ' || check->str[*i] == '\t'))
		(*i)++;
	check->ot = join_to_str(check->ot, '\x07');
	if (check->str[*i] != '"' && check->str[*i] != '\'' \
		&& find_separator(check->split, &check->str[*i]) == -1)
		check->ot = join_to_str(check->ot, check->str[*i]);
	else
		(*i)--;
}

static void	fill_with_nonpr_char(t_check *check)
{
	int	i;

	i = 0;
	while (check->str && check->str[i])
	{
		check->sid = find_separator(check->split, &check->str[i]);
		if (check->str[i] == '"' || check->str[i] == '\'')
			check_quote(check, &i);
		else if (check->sid != -1 && check->sq == 0 && check->dq == 0)
		{
			check->ot = join_to_str(check->ot, '\x07');
			check->ot = ft_strjoin(check->ot, check->split[check->sid]);
			check->ot = join_to_str(check->ot, '\x07');
			i += ft_strlen(check->split[check->sid]) - 1;
		}
		else if ((check->str[i] == ' ' || check->str[i] == '\t') \
			&& (check->sq == 0 && check->dq == 0))
			check_space_tab(check, &i);
		else
			check->ot = join_to_str(check->ot, check->str[i]);
		if (check->str[i])
			i++;
	}
	free_double_ptr(check->split);
}

int	split_and_fill_list(char *output, t_tokens **tokens)
{
	char		**split;
	int			i;
	t_check		*check;

	*tokens = NULL;
	split = NULL;
	i = 0;
	check = malloc(sizeof(t_check));
	if (!check)
		print_error(NULL, NULL, 1);
	if (init_check(check, output) == -1)
		return (-1);
	fill_with_nonpr_char(check);
	split = ft_split(check->ot, '\x07');
	free(check->ot);
	free(check);
	while (split && split[i])
		create_tokens(tokens, ft_strdup(split[i++]));
	free_double_ptr(split);
	return (0);
}
