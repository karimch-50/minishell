/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:19:01 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 18:41:31 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*_export(t_env *env)
{
	t_env	*export;
	t_env	*tmp_env;

	tmp_env = env;
	export = NULL;
	while (tmp_env)
	{
		add_to_env(&export, ft_strdup(tmp_env->var), ft_strdup(tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (export);
}

void	print_export(t_env *export)
{
	t_env	*tmp_export;

	tmp_export = export;
	while (tmp_export)
	{
		if (tmp_export->value != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp_export->var, 1);
			ft_putstr_fd("=\"", 1);
			print_value(tmp_export->value);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp_export->var, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp_export = tmp_export->next;
	}
}

int	search_var(t_env *export, char *var)
{
	t_env	*tmp_export;

	tmp_export = export;
	while (tmp_export)
	{
		if (ft_strcmp(tmp_export->var, var) == 0)
			return (1);
		tmp_export = tmp_export->next;
	}
	return (0);
}

void	edit_value2(t_env *exp_or_env, char *var, size_t equal, char *str)
{
	t_env	*tmp_exp_env;

	tmp_exp_env = exp_or_env;
	while (tmp_exp_env)
	{
		if (ft_strcmp(tmp_exp_env->var, var) == 0)
		{
			free(tmp_exp_env->value);
			if (equal == ft_strlen(str))
				tmp_exp_env->value = ft_strdup("");
			else
			{
				if (str[equal + 1] == '\0')
					tmp_exp_env->value = ft_strdup("");
				else
					tmp_exp_env->value = ft_strdup((ft_strchr(str, '=') + 1));
			}
			break ;
		}
		tmp_exp_env = tmp_exp_env->next;
	}
	if (!tmp_exp_env)
		add_to_env(&exp_or_env, ft_strdup(var), \
			ft_strdup((ft_strchr(str, '=') + 1)));
}

void	edit_value(t_env *env, t_env *export, char *str)
{
	char		*var;
	size_t		equal;

	equal = find_equale(str);
	var = ft_substr(str, 0, equal);
	edit_value2(export, var, equal, str);
	edit_value2(env, var, equal, str);
	free(var);
}
