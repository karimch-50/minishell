/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:25:35 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/17 14:32:33 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(t_global *global)
{
	char	cu_wo_di[PATH_MAX];

	if (getcwd(cu_wo_di, sizeof(cu_wo_di)) != NULL)
	{
		ft_putstr_fd(cu_wo_di, 1);
		ft_putstr_fd("\n", 1);
		global->exit_status = 0;
	}
	else
	{
		perror("minishell");
		global->exit_status = 1;
	}
}

void	print_value(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_strchr("`$\"", str[i]))
		{
			ft_putchar_fd('\\', 1);
			ft_putchar_fd(str[i], 1);
		}
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}	
}
