/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:34:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 17:48:48 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_env_exp2(t_env **export, t_env **env, char *str, size_t equal)
{
	char	*value;

	value = NULL;
	if (equal == ft_strlen(str))
	{
		add_to_env(export, ft_strdup(str), NULL);
		return ;
	}
	else if (str[equal + 1] == '\0')
		value = ft_strdup("");
	else
		value = ft_strdup((ft_strchr(str, '=') + 1));
	add_to_env(export, ft_substr(str, 0, equal), ft_strdup(value));
	add_to_env(env, ft_substr(str, 0, equal), value);
}

static void	error_message(char *arg, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	identifier(char *str, char *exp_uns)
{
	int	i;

	i = 0;
	if ((str[i] == '_' && (str[i + 1] && str[i + 1] == '=')) || str[i] == '#')
		return (1);
	if (str[i] == '=' || ft_isdigit(str[i]) || str[i] == '\0')
	{
		error_message(exp_uns, str);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] == '_')
			{
				i++;
				continue ;
			}
			error_message(exp_uns, str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_env_exp3(t_env **env, t_env **export, t_args *arg, int *check_exit)
{
	size_t		equal;
	char		*var;

	while (arg && arg->str)
	{
		if (identifier(arg->str, "export") == 1)
		{
			if (arg->str[0] == '#')
				break ;
			*check_exit = 1;
			arg = arg->next;
			continue ;
		}
		equal = find_equale(arg->str);
		var = ft_substr(arg->str, 0, equal);
		if (search_var(*export, var) == 1)
		{
			if (ft_strchr(arg->str, '=') != NULL)
				edit_value(*env, *export, arg->str);
		}
		else
			add_env_exp2(export, env, arg->str, equal);
		free(var);
		arg = arg->next;
	}
}

void	add_to_export_or_print(t_global *global, t_env **env, \
	t_env **export, t_args *args)
{
	t_args		*arg;
	int			check_exit;

	check_exit = 0;
	if (args)
	{
		if (!args->next || (args->next && args->next->str[0] == '#'))
		{
			print_export(*export);
			global->exit_status = 0;
		}
		else
		{
			arg = args->next;
			add_env_exp3(env, export, arg, &check_exit);
			global->exit_status = check_exit;
		}
	}
}
