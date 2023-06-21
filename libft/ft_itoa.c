/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:49:35 by kchaouki          #+#    #+#             */
/*   Updated: 2022/10/12 15:50:38 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbrs(int x)
{
	int	counter;

	counter = 0;
	if (x < 0)
		counter++;
	while (x != 0)
	{
		counter++;
		x /= 10;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*ret_num;
	int		len;

	len = count_nbrs(n);
	if (n == 0 || n == -0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ret_num = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret_num)
		return (0);
	if (n < 0)
	{
		n *= -1;
		ret_num[0] = '-';
	}
	ret_num[len--] = '\0';
	while (n != 0)
	{
		ret_num[len--] = n % 10 + '0';
		n /= 10;
	}
	return (ret_num);
}
