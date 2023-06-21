/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:58:29 by kchaouki          #+#    #+#             */
/*   Updated: 2022/10/03 17:25:51 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ret_s;

	ret_s = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!ret_s)
		return (0);
	i = 0;
	while (s[i])
	{
		ret_s[i] = f(i, s[i]);
		i++;
	}
	ret_s[i] = '\0';
	return (ret_s);
}
