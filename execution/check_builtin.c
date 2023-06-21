/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:24:38 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 16:52:03 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtins(t_global *global, t_cmdshell *all_cmds)
{
	char	*command;
	t_args	*args;

	args = all_cmds->cmds->args;
	command = all_cmds->cmds->args->str;
	if (ft_strncmp("export", command, ft_strlen("export")) == 0)
		add_to_export_or_print(global, &global->env, &global->export, args);
	if (ft_strncmp("env", command, ft_strlen("env")) == 0)
		print_env(global);
	if (ft_strncmp("unset", command, ft_strlen("unset")) == 0)
		unset(global, &global->env, &global->export, args);
	if (ft_strncmp("exit", command, ft_strlen("exit")) == 0)
		exitt(global, args);
	if (ft_strncmp("pwd", command, ft_strlen("pwd")) == 0)
		pwd(global);
	if (ft_strncmp("cd", command, ft_strlen("cd")) == 0)
		cd(global, args, global->export);
	if (ft_strncmp("echo", command, ft_strlen("echo")) == 0)
		echo(global, args);
}

int	is_builtin(char *token)
{
	if (!ft_strcmp(token, "echo"))
		return (1);
	else if (!ft_strcmp(token, "cd"))
		return (1);
	else if (!ft_strcmp(token, "pwd"))
		return (1);
	else if (!ft_strcmp(token, "env"))
		return (1);
	else if (!ft_strcmp(token, "export"))
		return (1);
	else if (!ft_strcmp(token, "unset"))
		return (1);
	else if (!ft_strcmp(token, "exit"))
		return (1);
	return (0);
}
