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

int encode_rgb(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

// check map extension
int has_cub_extension(const char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 4)
		return(0);
	return(ft_strncmp(filename + (len - 4 ), ".cub", 4) == 0);
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
	int count = 0;

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
	int		len = 0;
	char	*word;

	while (str[len] && !is_sep(str[len], charset))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	for (int i = 0; i < len; i++)
		word[i] = str[i];
	word[len] = '\0';
	return (word);
}

char	**ft_split_tokens(const char *str, const char *charset)
{
	int		words = count_words(str, charset);
	char	**result = malloc(sizeof(char *) * (words + 1));
	int		i = 0;

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
