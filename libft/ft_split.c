/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquintan <tquintan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:57:40 by tquintan          #+#    #+#             */
/*   Updated: 2021/06/11 15:16:24 by tquintan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **arr, int index)
{
	while (index >= 0)
	{
		free(arr[index]);
		index--;
	}
	free(arr);
}

size_t	word_counter(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] && s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	*word_creator(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}

char	**splitalloc(int amount_word)
{
	char	**a;

	a = (char **)malloc((amount_word + 1) * sizeof(char *));
	if (!a)
		return (NULL);
	return (a);
}

char	**ft_split(char const *s, char c)
{
	size_t	k;
	char	**a;
	size_t	amount_word;

	k = 0;
	if (s == NULL)
		return (0);
	amount_word = word_counter(s, c);
	a = splitalloc(amount_word);
	while (*s != '\0')
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			a[k] = word_creator(s, c);
			if (!a[k])
				ft_free(a, k - 1);
			k++;
			while (*s && *s != c)
				s++;
		}
	}
	a[k] = NULL;
	return (a);
}
