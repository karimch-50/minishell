/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:48 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 13:20:29 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_asterisks(char	*str)
{
	int	i;

	i = 0;
	while (str[i] == '*')
		i++;
	return (i);
}

static int	is_match(char *str, char *pattern)
{
	t_vars	vars;

	vars.last_p = ((vars.last_s = -1), -1);
	vars.i = ((vars.j = 0), 0);
	while (str[vars.i])
	{
		if (pattern[vars.j] == str[vars.i])
			vars.i += ((vars.j++), 1);
		else if (pattern[vars.j] == '*')
		{
			vars.last_s = ((vars.last_p = vars.j), vars.i);
			vars.j++;
		}
		else if (vars.last_p != -1)
		{
			vars.j = ((vars.i = vars.last_s + 1), vars.last_p + 1);
			vars.last_s++;
		}
		else
			return (0);
	}
	vars.j += skip_asterisks(&pattern[vars.j]);
	return (pattern[vars.j] == '\0');
}

t_tokens	*wildcard(char *arg)
{
	struct dirent	*entity;
	t_tokens		*tokens;
	DIR				*dir;

	dir = opendir(".");
	tokens = NULL;
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		entity = readdir(dir);
		if (entity == NULL)
			break ;
		if (arg[0] != '.' && entity->d_name[0] == '.')
			continue ;
		if (arg && is_match(entity->d_name, arg))
			create_tokens(&tokens, ft_strdup(entity->d_name));
	}
	closedir(dir);
	if (!tokens)
		create_tokens(&tokens, ft_strdup(arg));
	return (tokens);
}
