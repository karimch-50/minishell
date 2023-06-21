/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:11:01 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/20 13:22:05 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* join a given path with a given command */
static char	*ft_join_command_path(char *path, char *cmd)
{
	char	*output;
	int		i;

	output = malloc(ft_strlen(cmd) + ft_strlen(path) + 2);
	if (!output)
		print_error(NULL, NULL, 1);
	i = 0;
	while (path && *path)
		output[i++] = *path++;
	output[i++] = '/';
	while (cmd && *cmd)
		output[i++] = *cmd++;
	output[i] = '\0';
	return (output);
}

/* Check the existance of a command and it's permission*/
static int	check_permission(char *cmd)
{
	struct stat	file_state;

	lstat(cmd, &file_state);
	if (S_ISDIR(file_state.st_mode))
		print_error(EIAD, cmd, 126);
	if (!S_ISREG(file_state.st_mode))
		print_error(NULL, cmd, 127);
	if (access(cmd, X_OK) == -1)
		print_error(EPD, cmd, 126);
	return (1);
}

/* get the exact command path */
char	*valid_command_path(char **paths, char *cmd)
{
	char	*command_path;

	command_path = NULL;
	if (ft_strchr(cmd, '/') && check_permission(cmd))
		return (cmd);
	while (paths && *paths)
	{
		command_path = ft_join_command_path(*paths, cmd);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		command_path = NULL;
		paths++;
	}
	if (!paths)
	{
		command_path = ft_join_command_path(".", cmd);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		else
			print_error(ENSFD, cmd, 127);
	}
	if (!command_path)
		print_error(ECNF, cmd, 127);
	return (NULL);
}

static char	*handle_current_dir(char *to_handle)
{
	char	*output;
	int		i;

	i = 0;
	output = NULL;
	while (to_handle && to_handle[i])
	{
		if (i == 0 && to_handle[i] == ':')
			output = join_to_str(output, '.');
		else if (to_handle[i] == ':' && to_handle[i + 1] \
		&& to_handle[i + 1] == ':')
		{
			output = join_to_str(output, to_handle[i++]);
			output = join_to_str(output, '.');
		}
		else if (to_handle[i] == ':' && to_handle[i + 1] == '\0')
		{
			output = join_to_str(output, ':');
			output = join_to_str(output, '.');
		}
		output = join_to_str(output, to_handle[i]);
		i++;
	}
	free(to_handle);
	return (output);
}

char	**get_paths(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->var, "PATH"))
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (NULL);
	if (env->value[0] == '\0')
		return (ft_split("\x05\x05", ' '));
	env->value = handle_current_dir(env->value);
	return (ft_split(env->value, ':'));
}
