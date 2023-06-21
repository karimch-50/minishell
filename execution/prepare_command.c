/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:20:27 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 12:59:13 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_args(t_args *args)
{
	t_args	*tmp;
	int		count;

	count = 0;
	tmp = args;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**get_args(t_cmdshell *cmd)
{
	char	**output;
	t_args	*new_args;
	t_args	*tmp;
	int		i;

	new_args = cmd->cmds->args;
	output = malloc(sizeof(char *) * (count_args(new_args) + 1));
	if (!output)
		print_error(NULL, NULL, 1);
	i = 0;
	tmp = new_args;
	while (tmp)
	{
		output[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	output[i] = NULL;
	return (output);
}

t_recipe	prepare_command(t_global *global, t_cmdshell *all_cmds)
{
	t_recipe	output;
	char		**paths;

	output.command = NULL;
	paths = get_paths(global->env);
	if (all_cmds->cmds->args == NULL)
		exit(0);
	if (all_cmds->cmds->args->str[0] == '\0')
		print_error(ECNF, all_cmds->cmds->args->str, 127);
	if (paths && !ft_strcmp(paths[0], "\x05\x05"))
		print_error(ENSFD, all_cmds->cmds->args->str, 127);
	output.args = get_args(all_cmds);
	output.command = valid_command_path(paths, output.args[0]);
	free_double_ptr(paths);
	output.envp = get_env(global->env);
	return (output);
}
