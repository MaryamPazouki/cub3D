/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 19:33:13 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 19:33:13 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

int	is_blank_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

// --- Helper: trim a line or return error ---
char	*safe_trim_line(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
	{
		free(line);
		fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}
	return (trimmed);
}

// --- Helper: check for garbage after map ---
int	check_garbage_after_map(char *line)
{
	fprintf(stderr, "\033[31mError: Garbage after map end:\033[0m %s\n", line);
	free(line);
	return (0);
}

// check the valide keywords for directive
int	is_directive(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!line[0] || !line[1] || !line[2])
		return (0);
	return ((ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		|| (line[0] == 'F' && ft_isspace(line[1])) || (line[0] == 'C'
			&& ft_isspace(line[1])));
}

// size_t	ft_strcspn(const char *s, const char *reject)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (s[i])
// 	{
// 		j = 0;
// 		while (j < reject[j])
// 		{
// 			if (s[i] == reject[j])
// 				return (i);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (i);
// }
