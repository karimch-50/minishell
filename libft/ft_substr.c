/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:02:26 by kchaouki          #+#    #+#             */
/*   Updated: 2023/02/09 12:53:00 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret_str;
	unsigned int	i;

	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - (size_t)start)
		len = ft_strlen(s) - (size_t)start;
	ret_str = (char *)malloc(sizeof(char) * len + 1);
	if (!s || !ret_str)
		return (0);
	i = 0;
	while (i < len)
	{
		ret_str[i] = s[start + i];
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}
