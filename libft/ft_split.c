/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:03:00 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/05 15:27:58 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	freemem(char **arr, int size)
{
	while (size--)
		free(arr[size]);
	free(arr);
	return (-1);
}

void	do_word(char *dest, char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
}

int	do_split(char **arr, char const *s, char c)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			arr[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (!arr[word])
				return (freemem(arr, word));
			do_word(arr[word], s + i, c);
			i += j;
			word++;
		}
	}
	return (0);
}

int	wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == c)
			|| (s[i + 1] == '\0' && s[i] != c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**arr;
	char	*empty;

	count = wordcount(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 2));
	if (!arr)
		return (NULL);
	empty = (char *)malloc(sizeof(char *));
	if (!empty)
		return (NULL);
	empty[0] = '\0';
	arr[0] = empty;
	arr[count + 1] = 0;
	if (do_split(arr + 1, s, c) == -1)
		return (NULL);
	return (arr);
}
