/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:45:12 by kchaouki          #+#    #+#             */
/*   Updated: 2022/10/10 12:16:04 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;
	size_t	len_dest_src;

	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	len_dest_src = len_dest + len_src;
	if (dstsize <= len_dest || dstsize == 0)
		return (len_src + dstsize);
	i = 0;
	dstsize = dstsize - len_dest - 1;
	while (src[i] != '\0' && i < dstsize)
		dst[len_dest++] = src[i++];
	dst[len_dest] = '\0';
	return (len_dest_src);
}
