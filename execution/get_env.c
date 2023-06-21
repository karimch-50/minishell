/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:39:42 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/14 09:49:05 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*ft_join_env(char *s1, char *s2)
{
	char	*output;
	int		i;

	output = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!output)
		print_error(NULL, NULL, 1);
	i = 0;
	while (s1 && *s1)
		output[i++] = *s1++;
	output[i++] = '=';
	while (s2 && *s2)
		output[i++] = *s2++;
	output[i] = '\0';
	return (output);
}

char	**get_env(t_env *env)
{
	char	**output;
	int		i;

	output = malloc(sizeof(char *) * (count_env(env) + 1));
	if (!output)
		print_error(NULL, NULL, 1);
	i = 0;
	while (env)
	{
		output[i++] = ft_join_env(env->var, env->value);
		env = env->next;
	}
	output[i] = NULL;
	return (output);
}
