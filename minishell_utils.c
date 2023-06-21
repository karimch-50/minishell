/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:39:59 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/17 14:57:12 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctl_ter(void)
{
	struct termios	ter;

	tcgetattr(0, &ter);
	ter.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &ter);
}

int	init_global(t_global **global, char **env)
{
	signal(SIGINT, sig_handl);
	signal(SIGQUIT, SIG_IGN);
	ctl_ter();
	*global = malloc(sizeof(t_global));
	if (!*global)
		print_error(NULL, NULL, 1);
	(*global)->exit_status = 0;
	(*global)->env = create_env(env);
	(*global)->export = _export((*global)->env);
	(*global)->prev_fd = -1;
	(*global)->all_commands = NULL;
	(*global)->pid = NULL;
	return (0);
}

char	*join_to_str(char *str, char c)
{
	char	*output;
	int		i;

	if (!str)
		output = malloc(2);
	else
		output = malloc(ft_strlen(str) + 2);
	if (!output)
		print_error(NULL, NULL, 1);
	i = 0;
	while (str && str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i++] = c;
	output[i] = '\0';
	free (str);
	return (output);
}

static void	detect_error(char *msg, char *arg)
{
	char	*error_msg;

	if (!msg && !arg)
	{
		error_msg = ft_strjoin(ft_strdup("minishell: "), strerror(errno));
		ft_putstr_fd(error_msg, 2);
		ft_putchar_fd('\n', 2);
		free (error_msg);
	}
	else if (!msg && arg)
	{
		arg = ft_strjoin(ft_strdup("minishell: "), arg);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		free (arg);
	}
}

void	print_error(char *msg, char *arg, int status)
{
	char	*error_msg;

	if (msg && !arg)
		ft_putstr_fd(msg, 2);
	else if ((!msg && !arg) || (!msg && arg))
		detect_error(msg, arg);
	else
	{
		arg = ft_strjoin(ft_strdup("minishell: "), arg);
		error_msg = ft_strjoin(arg, msg);
		ft_putstr_fd(error_msg, 2);
		free (error_msg);
	}
	if (status != -1)
		exit(status);
}
