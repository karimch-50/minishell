/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:03:23 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/20 17:50:12 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	error_message(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

unsigned long	my_ft_atoi(char *str, int sign)
{
	unsigned long		ret;
	int					i;

	ret = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		ret = ret * 10 + str[i++] - '0';
		if (ret > 0 && ((sign == -1 && ret - 1 > LONG_MAX) \
			|| (ret > LONG_MAX && sign == 1)))
		{
			error_message(str);
			return (255);
		}
	}
	return (ret * sign);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	exitt(t_global *global, t_args *args)
{
	if (args)
	{
		ft_putstr_fd("exit\n", 2);
		if (!args->next)
			exit(global->exit_status);
		if (args->next->next && check_arg(args->next->str) == 0)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			global->exit_status = 1;
		}
		else if (check_arg(args->next->str) == 1)
		{
			error_message(args->next->str);
			exit(255);
		}
		else
			exit(my_ft_atoi(args->next->str, 1));
	}
}
