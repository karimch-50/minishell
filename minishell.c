/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 19:15:14 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_r;

void	sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		if (g_r == 0)
			write(1, "\n", 1);
		rl_catch_signals = 0;
		close(0);
		g_r += 1;
	}
}

int	minishell(t_global *global)
{
	char		*line;
	int			ret;

	line = readline("minishell ~ ");
	if (line)
	{
		if (line[0] != 0)
			add_history(line);
		else
			return (free(line), 2);
		ret = fill_global_struct(&global, line);
		if (ret == -1)
			return (free_commands(global->all_commands), free(line), 2);
		if (ret == -2)
			return (free (line), 2);
		execution(global);
	}
	else
	{
		if (rl_catch_signals == 0)
			return (2);
		else
			return (1);
	}
	return (free_commands(global->all_commands), free(line), 2);
}

int	finish(t_global *global)
{
	int	final_exit;

	final_exit = global->exit_status;
	global_free(global);
	ft_putstr_fd("exit\n", 2);
	return (final_exit);
}

int	main(int argc, char **argv, char **env)
{
	t_global	*global;
	int			tmp_gr;
	int			fd;

	(void) argc;
	(void) argv;
	init_global(&global, env);
	fd = dup(0);
	g_r = 0;
	tmp_gr = 0;
	while (1)
	{
		dup2(fd, 0);
		rl_catch_signals = 1;
		if (g_r != tmp_gr)
			global->exit_status = 1;
		tmp_gr = g_r;
		if (minishell(global) == 2)
			continue ;
		else
			break ;
	}
	return (finish(global));
}
