/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:21:36 by rabduras          #+#    #+#             */
/*   Updated: 2019/11/28 15:00:59 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words_count(const char *s, char c)
{
	int		toggle;
	size_t	words;
	char	*cpy;

	toggle = 0;
	words = 0;
	cpy = (char *)s;
	while (*cpy)
	{
		if (*cpy != c && !toggle)
		{
			toggle = 1;
			words++;
		}
		if (*cpy == c && toggle)
			toggle = 0;
		cpy++;
	}
	return (words);
}

static size_t	delim_strlen(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		*nextword(const char *s, char c, size_t *n)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	*res;

	i = *n;
	j = 0;
	while (s[i] == c)
		i++;
	count = delim_strlen((s + i), c);
	res = (char*)malloc(sizeof(char) * (count + 1));
	while (count--)
		res[j++] = s[i++];
	res[j] = '\0';
	*n = i;
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	char	*cpy;
	size_t	n;
	int		i;
	int		count;
	char	**res;

	i = 0;
	n = 0;
	if (!s || !c)
		return (NULL);
	count = words_count(s, c);
	cpy = (char *)s;
	res = (char**)malloc(sizeof(char*) * (count + 1));
	if (res != NULL)
	{
		while (i < count)
			res[i++] = nextword(cpy, c, &n);
		res[i] = 0;
		return (res);
	}
	return (NULL);
}
