/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:33:16 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/19 22:53:02 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	*alloc_word_mem(char *str, char c)
{
	int		i;
	int		count_letters;
	char	*ret_word;

	count_letters = 0;
	while (str && str[count_letters] != c && str[count_letters])
		count_letters++;
	ret_word = (char *)malloc(count_letters * sizeof(char) + 1);
	if (!ret_word)
		return (0);
	i = 0;
	while (str && i < count_letters)
	{
		ret_word[i] = str[i];
		i++;
	}
	ret_word[i] = '\0';
	return (ret_word);
}

char	**mem_free(char **ret, int j)
{
	while (j > 0)
	{
		j--;
		free(ret[j]);
	}
	free(ret);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ret_split;
	int		i;
	int		j;

	ret_split = ((i = 0), (j = 0), NULL);
	ret_split = malloc(sizeof(char *) * (word_count((char *)s, c) + 1));
	if (!ret_split)
		return (0);
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			ret_split[j] = alloc_word_mem((char *)&s[i], c);
			if (!ret_split[j])
				return (mem_free(ret_split, j));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ret_split[j] = 0;
	return (ret_split);
}
