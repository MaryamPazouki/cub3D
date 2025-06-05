/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 07:57:13 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 07:57:13 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

int	encode_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// ---------------ft_split_tokens.c----------------

static int	is_sep(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	count_words(const char *str, const char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_sep(*str, charset))
			str++;
		if (*str && !is_sep(*str, charset))
		{
			count++;
			while (*str && !is_sep(*str, charset))
				str++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *str, const char *charset)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (str[len] && !is_sep(str[len], charset))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split_tokens(const char *str, const char *charset)
{
	int		words;
	char	**result;
	int		i;

	words = count_words(str, charset);
	result = malloc(sizeof(char *) * (words + 1));
	i = 0;
	if (!result || !str)
		return (NULL);
	while (*str)
	{
		while (*str && is_sep(*str, charset))
			str++;
		if (*str && !is_sep(*str, charset))
		{
			result[i++] = malloc_word(str, charset);
			while (*str && !is_sep(*str, charset))
				str++;
		}
	}
	result[i] = NULL;
	return (result);
}
