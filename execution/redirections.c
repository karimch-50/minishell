/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:15:16 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/14 20:22:16 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_redirection(char *infile)
{
	int	fd;

	if (access (infile, F_OK))
	{
		print_error(ENSFD, infile, -1);
		return (-1);
	}
	if (access (infile, R_OK))
	{
		print_error(EPD, infile, -1);
		return (-1);
	}
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		print_error(NULL, NULL, -1);
		return (-1);
	}
	return (fd);
}

int	output_redirection(char *outfile)
{
	int	fd;

	if (access (outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		print_error(EPD, outfile, -1);
		return (-1);
	}
	fd = open (outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(NULL, NULL, -1);
		return (-1);
	}
	return (fd);
}

int	append_output(char *outfile)
{
	int	fd;

	if (!access (outfile, F_OK) && access(outfile, W_OK))
	{
		print_error(EPD, outfile, -1);
		return (-1);
	}
	fd = open (outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(NULL, NULL, -1);
		return (-1);
	}
	return (fd);
}
