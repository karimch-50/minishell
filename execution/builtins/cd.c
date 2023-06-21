/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:22:53 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/15 18:08:55 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_no_arg(t_global *global, t_args *args, t_env *export)
{
	t_env	*tmp_exp;

	if (!args)
		return ;
	else
	{
		tmp_exp = export;
		while (tmp_exp)
		{
			if (ft_strcmp(tmp_exp->var, "HOME") == 0)
			{
				chdir(tmp_exp->value);
				global->exit_status = 0;
				return ;
			}
			tmp_exp = tmp_exp->next;
		}
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		global->exit_status = 1;
	}
}

static void	error_message(char *arg, char *message)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	cd(t_global *global, t_args	*args, t_env *export)
{
	char	*dir;

	dir = NULL;
	if (args && args->next)
	{
		if (chdir(args->next->str) == -1)
		{
			dir = ft_strjoin(ft_strdup("./"), args->next->str);
			if (chdir(dir) == -1)
			{
				error_message(args->next->str, strerror(errno));
				global->exit_status = 1;
			}
			else
				global->exit_status = 0;
			free(dir);
		}
		else
			global->exit_status = 0;
	}
	else
		cd_no_arg(global, args, export);
}
