/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:09:09 by rokerjea          #+#    #+#             */
/*   Updated: 2022/04/19 17:09:10 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	wordcount;

	wordcount = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			wordcount++;
		i++;
	}
	return (wordcount);
}

int	ft_lenword(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	return (j + 1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		wnum;
	int		i;
	int		j;

	res = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!res)
		return (NULL);
	wnum = 0;
	i = 0;
	while (wnum < ft_wordcount(s, c))
	{
		j = 0;
		while (s[i] == c)
			i++;
		res[wnum] = malloc(sizeof(char) * (ft_lenword(s, c, i)));
		if (!(res[wnum]))
			return (ft_freetab(res));
		while (s[i] != c && s[i])
			res[wnum][j++] = s[i++];
		res[wnum][j] = '\0';
		wnum++;
	}
	res[wnum] = 0;
	return (res);
}
