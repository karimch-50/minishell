/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:42:07 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/17 17:54:43 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_parantheces(char *str)
{
	char	*output;
	int		count;
	int		i;
	int		j;

	i = 1;
	j = 0;
	count = ft_strlen(str);
	output = malloc(sizeof(char) * count - 1);
	if (!output)
		print_error(NULL, NULL, 1);
	while (str && i < count - 1)
		output[j++] = str[i++];
	output[j] = '\0';
	return (output);
}

void	run_subshell(t_global *global, t_cmdshell *cmd, int i, int count)
{
	t_global	*new_global;
	char		*rem_par;

	signal(SIGINT, SIG_IGN);
	global->pid[i] = fork();
	if (global->pid[i] == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
	else if (global->pid[i] == 0)
	{
		rem_par = remove_parantheces(cmd->cmds->subshell);
		signal(SIGINT, SIG_DFL);
		read_write_pipe(global, cmd, i, count);
		if (manage_redirection(global, cmd->cmds->redis))
			exit(1);
		init_global(&new_global, get_env(global->env));
		fill_global_struct(&new_global, rem_par);
		execution(new_global);
		free_commands(new_global->all_commands);
		free(rem_par);
		exit(new_global->exit_status);
	}
}
