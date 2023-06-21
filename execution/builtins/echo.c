/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:07:25 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/17 18:22:14 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_opt(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	else if (str[0] == '-' && str[1] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo2(t_args *tmp_args, int check)
{
	int	r;

	r = 0;
	while (tmp_args)
	{
		while (check_opt(tmp_args->str) == 1 && check == 0)
		{
			r = 1;
			tmp_args = tmp_args->next;
			if (!tmp_args)
				return ;
			continue ;
		}
		if (tmp_args->next)
		{
			check = 1;
			ft_putstr_fd(tmp_args->str, 1);
			ft_putstr_fd(" ", 1);
		}
		else
			ft_putstr_fd(tmp_args->str, 1);
		tmp_args = tmp_args->next;
	}
	if (r == 0)
		ft_putstr_fd("\n", 1);
}

void	echo(t_global *global, t_args *args)
{
	t_args	*tmp_args;

	if (args)
	{
		if (args->next)
		{
			tmp_args = args->next;
			echo2(tmp_args, 0);
		}
		else
			ft_putstr_fd("\n", 1);
		global->exit_status = 0;
	}
}
